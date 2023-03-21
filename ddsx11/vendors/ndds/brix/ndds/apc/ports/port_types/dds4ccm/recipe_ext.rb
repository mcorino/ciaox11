#--------------------------------------------------------------------
# @file    recipe_ext.rb
# @author  Martin Corino
#
# @brief  DDS4CCM SEV interaction implementation specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC
  module DDS4CCM
    # reopen Extension module for DataIdlRecipe
    module DataIDLExtension
      def add_ndds_proj(fidl)
        # Is there already an ndds project for this recipe?
        prj_dependencies = fidl.project_dependencies
        if mpc_idl_obj = mpc_file[:ddsx11_ndds_idl_gen]
          # return if the specified IDL file is already part of MPC project
          return if mpc_idl_obj.has_project_file?(fidl.full_path)

          mpc_stub_obj = mpc_file[:stub]

          mpc_idl_types_obj = mpc_file[:ddsx11_ndds_types_gen]

          mpc_types_impl_obj = mpc_file[:ddsx11_ndds_types]
        else
          mpc_idl_obj = MPC::IDLProject.new(:ddsx11_ndds_idl_gen, self)
          mpc_file.add_mpc_project(mpc_idl_obj)
          #set idl_includes set in recipe and set in  project file
          mpc_idl_obj.includes << idl_includes << project.idl_includes

          # make sure :stub projects exist
          add_stub_proj(fidl)
          # get stub library project
          mpc_stub_obj = mpc_file[:stub]
          # extend stub library project
          mpc_stub_obj.base_projects << %w{ddsx11_stub}
          mpc_stub_obj.project_dependencies << "#{mpc_id}_ddsx11_ndds_idl_gen"

          mpc_idl_types_obj = MPC::IDLProject.new(:ddsx11_ndds_types_gen, self)
          mpc_idl_types_obj.includes << idl_includes << project.idl_includes
          mpc_file.add_mpc_project(mpc_idl_types_obj)

          mpc_types_impl_obj = MPC::NDDSTsStubProject.new(self)
          mpc_file.add_mpc_project(mpc_types_impl_obj)
        end

        # ddsx11_ndds_idl_gen project exist, but idl files is not already part of this project,
        # so add with add_project_file the idl file to idl_files
        # for ami idl-project and to sources and headers for ami stub compile project
        mpc_idl_obj.add_project_file(fidl.full_path)

        # add state/event typed entities interfaces generated by :ddsx11_ndds_idl_gen project for idl file
        mpc_stub_obj.sources << (dds_typed_entities_stub_noext(fidl) + '.cpp')
        mpc_stub_obj.headers << (dds_typed_entities_stub_noext(fidl) + '.h')

        mpc_idl_types_obj.add_project_file(dds_idl_file_path(fidl.full_path))
        mpc_types_impl_obj.add_project_file(fidl.full_path)

        # register resulting project dependencies for IDL file
        prj_dependencies <<
            MPC::CompileDependency.new(:ddsx11_ndds_idl_gen, self) <<
            MPC::LinkDependency.new(:stub, self) <<
            MPC::CompileDependency.new(:ddsx11_ndds_types_gen, self) <<
            MPC::LinkDependency.new(:ddsx11_ndds_types, self,
                                    MPC::LinkDependency.new(:stub, self))

        mpc_types_impl_obj.add_dependencies(prj_dependencies, :stub)

        fidl.includes.each do|ifidl|
          ifidl.interaction_types << :sev
        end
      end
    end # DataIDLExtension
  end # DDS4CCM
end
