if (PARAVIEW_USE_MPI)
  pv_plugin(PhastaSyncIOReader
    DESCRIPTION "Phasta SyncIO Reader"
    # uncomment AUTOLOAD to have the plugin automatically loaded. Note
    # though that this isn't working in PV 5.2 and probably earlier
    #AUTOLOAD
    DEFAULT_ENABLED)
endif()
