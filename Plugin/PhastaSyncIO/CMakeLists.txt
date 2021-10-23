set(classes
	vtkPhastaSyncIOMetaReader
	vtkPhastaSyncIOReader
	)
vtk_module_add_module(PhastaSyncIO FORCE_STATIC
	CLASSES ${classes})
paraview_add_server_manager_xmls( XMLS PhastaSyncIO.xml)
