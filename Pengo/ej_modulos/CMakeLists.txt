#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Animation.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/StaticAnimation.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/IceBlock.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Block.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Character.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Pengo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SnoBee.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Labyrinth.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Collision.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Swarm.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Level.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MazeGenerator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/DiamondBlock.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/StarPlay.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Wall.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Egg.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

