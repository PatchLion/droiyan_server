QXORM_LIB_PATH="H:/git_repositories/d_server_sources/QxOrmLib"
BOOST_ROOT_PATH="H:/git_repositories/boost_1_62_0"

isEmpty(QXORM_LIB_PATH) {
error("Error in DBDataManager.pri configuration file : QXORM_LIB_PATH variable is empty!")
} # isEmpty(QXORM_LIB_PATH)

!exists($${QXORM_LIB_PATH}){
error("Check if QxOrm library file exists : $${QXORM_LIB_PATH}")
}
QT += sql

DEFINES += _BUILDING_QX_DATABASE

INCLUDEPATH+= $${QXORM_LIB_PATH}/include \
            $${BOOST_ROOT_PATH}

LIBS += -L$${QXORM_LIB_PATH}/lib/$(Platform)/$(Configuration)/ -lQxOrm
