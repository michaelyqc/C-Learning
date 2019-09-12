#!/usr/bin/python
# -*- coding: utf-8 -*-

from ambari_commons.os_family_impl import OsFamilyImpl
from resource_management.libraries.script.script import Script
from resource_management import *
from resource_management.libraries.functions import check_process_status

from service_action import *

@OsFamilyImpl(os_family=OsFamilyImpl.DEFAULT)
class ResourceIsolationService(Script):

  # because resource isolation service is virtual, so no real service is installed
  def install(self, env):
    Logger.info("Install resource isolation service")
    import params
    env.set_params(params)
    
    self.install_packages(env)
    
  # because resource isolation service is virtual, so no configure file temporary
  def configure(self, env, upgrade_type=None):
    Logger.info("Configure the resource isolation service")
    import params
    env.set_params(params)
    
  def start(self, env, upgrade_type=None):
    Logger.info("Start the resource isolation service")
    import params
    env.set_params(params)
    
    self.configure(env)
    start_resource_isolation_service(env)

  def stop(self, env, upgrade_type=None):
    Logger.info("Stop the resource isolation service")
    import params
    env.set_params(params)
    
    stop_resource_isolation_service(env)

  def updateconfig(self, env, upgrade_type=None):
    Logger.info("Update the resource isolation service's subgroup resource configure")
    import params
    env.set_params(params)
    
    update_subgroup_resource_config(env)

  def status(self, env):
    import params
    env.set_params(params)
  
    resource_isolation_service_status(env)



if __name__ == "__main__":
  ResourceIsolationService().execute()
