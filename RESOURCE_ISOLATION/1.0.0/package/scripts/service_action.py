#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os

from resource_management import *
from resource_management.libraries.functions import check_process_status


def mount_cgroup(env):
  import params
  try:
    # clean dir
    cmd = "rm -rf " + params.resource_isolation_data_dir
    Execute(cmd, user='root')
    
    File(params.mount_cgroup_subsys, 
         owner='root',
         group='root',
         mode=0755,
         content=Template("mount_cgroup_subsys.sh.j2")
    )
    
    # prepare umount script to avoid rely on ambari-server config
    Directory(params.resource_isolation_data_dir, create_parents = True)
    File(params.umount_cgroup_subsys, 
         owner='root',
         group='root',
         mode=0755,
         content=Template("umount_cgroup_subsys.sh.j2")
    )
    
    mount_cgroup_subsys_cmd = "bash -x {mount_cgroup_subsys}"
    cmd = format(mount_cgroup_subsys_cmd)
    print cmd
    
    Execute(cmd, logoutput=True)
    
  except:
    raise


def umount_cgroup(env):
  import params
  try:
    if os.path.exists(params.umount_cgroup_subsys):
        umount_cgroup_subsys_cmd = "bash -x {umount_cgroup_subsys}"
        cmd = format(umount_cgroup_subsys_cmd)
        print cmd
        Execute(cmd, logoutput=True)
        
        # clean garbage file
        cmd = "rm -f " + params.umount_cgroup_subsys
        Execute(cmd, user='root')
  except:
    raise


def create_or_update_grouping(env, group_resource_config, group_index, action):
  import params
  try:
    resource_config_dict = {}
    
    # subgroup name, service list
    resource_config_dict['open_group'] = group_resource_config['open_group']
    resource_config_dict['moving_descendant_process_pid'] = group_resource_config['moving_descendant_process_pid']
    resource_config_dict['group_name'] = group_resource_config['group_name']
    resource_config_dict['service_pid_file_list'] = group_resource_config['service_pid_file_list']
    
    # cpu subsystem config
    resource_config_dict['cfs_period_us'] = group_resource_config['cpu.cfs_period_us']
    resource_config_dict['cfs_quota_us'] = group_resource_config['cpu.cfs_quota_us']
    resource_config_dict['rt_period_us'] = group_resource_config['cpu.rt_period_us']
    resource_config_dict['rt_runtime_us'] = group_resource_config['cpu.rt_runtime_us']
    resource_config_dict['cpu_shares'] = group_resource_config['cpu.shares']
    
    # memory subsystem config
    resource_config_dict['mem_limit_in_bytes'] = group_resource_config['memory.limit_in_bytes']
    resource_config_dict['memsw_limit_in_bytes'] = group_resource_config['memory.memsw.limit_in_bytes']
    resource_config_dict['move_charge_at_immigrate'] = group_resource_config['memory.move_charge_at_immigrate']
    resource_config_dict['force_empty'] = group_resource_config['memory.force_empty']
    resource_config_dict['oom_control'] = group_resource_config['memory.oom_control']
    resource_config_dict['use_hierarchy'] = group_resource_config['memory.use_hierarchy']
    
    # cpuset subsystem config
    resource_config_dict['cpus'] = group_resource_config['cpuset.cpus']
    resource_config_dict['cpu_exclusive'] = group_resource_config['cpuset.cpu_exclusive']
    resource_config_dict['mems'] = group_resource_config['cpuset.mems']
    resource_config_dict['mem_exclusive'] = group_resource_config['cpuset.mem_exclusive']
    resource_config_dict['memory_pressure_enabled'] = group_resource_config['cpuset.memory_pressure_enabled']
    
    # blkio subsystem config
    resource_config_dict['read_bps_device'] = group_resource_config['blkio.throttle.read_bps_device']
    resource_config_dict['write_bps_device'] = group_resource_config['blkio.throttle.write_bps_device']
    resource_config_dict['read_iops_device'] = group_resource_config['blkio.throttle.read_iops_device']
    resource_config_dict['write_iops_device'] = group_resource_config['blkio.throttle.write_iops_device']
    resource_config_dict['blkio_weight'] = group_resource_config['blkio.weight']
    resource_config_dict['blkio_weight_device'] = group_resource_config['blkio.weight_device']
    resource_config_dict['blkio_leaf_weight'] = group_resource_config['blkio.leaf_weight']
    resource_config_dict['blkio_leaf_weight_device'] = group_resource_config['blkio.leaf_weight_device']
    
    # net_cls, net_prio subsystem config
    resource_config_dict['net_cls_classid'] = group_resource_config['net_cls.classid']
    resource_config_dict['total_bandwith'] = group_resource_config['net_cls.total_bandwith']
    resource_config_dict['assured_rate'] = group_resource_config['net_cls.assured_rate']
    resource_config_dict['ceil_rate'] = group_resource_config['net_cls.ceil_rate']
    resource_config_dict['net_prio_ifpriomap'] = group_resource_config['net_prio.ifpriomap']
    
    # resource_config_dict[''] = group_resource_config['service_pid_file_list']
    env.set_params(resource_config_dict)
    
    Directory(params.update_service_pid_script_dir, create_parents = True)
    # preparing delete resource isolation group script, avoid rely on ambari-server config
    File(os.path.join(params.resource_isolation_data_dir, 
                      'delete_resource_isolation_group-' + str(group_index) + '.sh'),
         owner='root',
         group='root',
         mode=0755,
         content=Template("delete_resource_isolation_group.sh.j2")
    )
    # generate shell script: update_service_pid.sh
    File(os.path.join(params.update_service_pid_script_dir, 
                      'update_service_pid-' + str(group_index) + '.sh'),
         owner='root',
         group='root',
         mode=0755,
         content=Template("update_service_pid.sh.j2")
    )
    if action == 'create':
        # generate shell script: create_resource_isolation_group.sh
        File(os.path.join(params.tmp_dir, 'create_resource_isolation_group.sh'),
             owner='root',
             group='root',
             mode=0755,
             content=Template("create_resource_isolation_group.sh.j2")
        )
        
        # create new resource isolation group and moving service pid to new group
        cmd = format("bash -x {tmp_dir}/create_resource_isolation_group.sh")
        Execute(cmd, logoutput=True)
    else:
        # generate shell script: update_isolation_group_config.sh
        File(os.path.join(params.tmp_dir, 'update_isolation_group_config.sh'),
             owner='root',
             group='root',
             mode=0755,
             content=Template("update_isolation_group_config.sh.j2")
        )
        
        # create new resource isolation group and moving service pid to new group
        cmd = format("bash -x {tmp_dir}/update_isolation_group_config.sh")
        Execute(cmd, logoutput=True)
        
  except:
    raise


def create_or_update_resource_isolation_group(env, action):
  import params
  try:
    for index in range(0, params.group_num):
        group_resource_config = params.config['configurations']['resource-isolation-group-' + str(index)]
        open_group = group_resource_config['open_group']
        if open_group == False:
            continue
        create_or_update_grouping(env, group_resource_config, index, action)
  except:
    raise


def delete_grouping(env, group_index):
  import params
  try:
    delete_resource_isolation_group_script = os.path.join(params.resource_isolation_data_dir, 
                      'delete_resource_isolation_group-' + str(group_index) + '.sh')
    if os.path.exists(delete_resource_isolation_group_script):
        Execute("bash -x " + delete_resource_isolation_group_script, logoutput=True)
        
        # delete delete_resource_isolation_group-*.sh
        cmd = "rm -f " + delete_resource_isolation_group_script
        Execute(cmd, user='root')
        
        # delete update_service_pid.sh
        cmd = format("rm -f {update_service_pid_script_dir}/update_service_pid-" + str(group_index) + ".sh")
        Execute(cmd, user='root')
  except:
    raise


def delete_resource_isolation_group(env):
  import params
  try:
    for index in range(params.max_group_num-1, -1, -1):
        delete_grouping(env, index)
  except:
    raise



def start_resource_isolation_service(env):
  import params
  env.set_params(params)
  
  try:
    if params.open_resource_isolation_service == True:
        # mount cgroup sub system 
        mount_cgroup(env)
        
        # create and configure resource isolation group 
        create_or_update_resource_isolation_group(env, 'create')
        
    # mark resource isolation service 
    # resource isolation service depend on operation system 
    Execute(('mkdir', '-p', params.resource_isolation_pid_path),
            logoutput = True,
            sudo = True
    )
    Execute(('touch', params.resource_isolation_pid_file),
            logoutput = True,
            sudo = True
    )
    Execute('echo 1 > ' + params.resource_isolation_pid_file,
            user='root'
    )
  except:
    raise



def stop_resource_isolation_service(env):
  import params
  env.set_params(params)
  
  try:
    # delete resource isolation group 
    delete_resource_isolation_group(env)
    # umount cgroup sub system 
    umount_cgroup(env)
    
    # umark resource isolation service 
    # cmd = "rm -f " + params.resource_isolation_pid_file
    Execute(('rm', '-f', params.resource_isolation_pid_file),
            logoutput = True,
            sudo = True
    )
    
  except:
    raise


def update_subgroup_resource_config(env):
  import params
  env.set_params(params)
  
  try:
    if params.open_resource_isolation_service == True:
        # update resource isolation group configure 
        create_or_update_resource_isolation_group(env, 'update')
    else:
        return
  except:
    raise


def resource_isolation_service_status(env):
  import params
  env.set_params(params)
  
  try:
    # update service pid, because some services having been restarted probably
    for index in range(0, params.max_group_num):
        update_service_pid_script = os.path.join(params.update_service_pid_script_dir,
                'update_service_pid-' + str(index) + '.sh')
        if os.path.exists(update_service_pid_script):
            Execute("bash -x " + update_service_pid_script, user='root')
    check_process_status(params.resource_isolation_pid_file)
  except:
    raise






