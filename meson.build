project('chat', ['cs', 'cpp'])

clasesc = [
       'servidor/ListaUsuarios.cpp',
       'servidor/Main.cpp',
       'servidor/Servidor.cpp',
       'servidor/Mensaje.cpp',
       'servidor/Sala.cpp',
       'servidor/Conexion.cpp'
       ]      				
clasescs = [
	 'cliente/Main.cs',
	 'cliente/Aplicacion.cs',
	 'cliente/Escribe.cs',
	 'cliente/Mensaje.cs',
	 'cliente/Parser.cs',
	 'cliente/Vista.cs'
	 ]

newtonsoft = meson.project_source_root() / 'libs/Newtonsoft.Json.dll'	


executable('cliente', sources : clasescs,cs_args : [
        '-r:' + newtonsoft
    ])
    
executable('servidor', sources : clasesc)
