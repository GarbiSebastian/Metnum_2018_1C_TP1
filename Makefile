#
#  There exist several targets which are by default empty and which can be
#  used for execution of your targets. These targets are usually executed
#  before and after some main targets. They are:
#
#     .build-pre:              called before 'build' target
#     .build-post:             called after 'build' target
#     .clean-pre:              called before 'clean' target
#     .clean-post:             called after 'clean' target
#     .clobber-pre:            called before 'clobber' target
#     .clobber-post:           called after 'clobber' target
#     .all-pre:                called before 'all' target
#     .all-post:               called after 'all' target
#     .help-pre:               called before 'help' target
#     .help-post:              called after 'help' target
#
#  Targets beginning with '.' are not intended to be called on their own.
#
#  Main targets can be executed directly, and they are:
#
#     build                    build a specific configuration
#     clean                    remove built files from a configuration
#     clobber                  remove all built files
#     all                      build all configurations
#     help                     print help mesage
#
#  Targets .build-impl, .clean-impl, .clobber-impl, .all-impl, and
#  .help-impl are implemented in nbproject/makefile-impl.mk.
#
#  Available make variables:
#
#     CND_BASEDIR                base directory for relative paths
#     CND_DISTDIR                default top distribution directory (build artifacts)
#     CND_BUILDDIR               default top build directory (object files, ...)
#     CONF                       name of current configuration
#     CND_PLATFORM_${CONF}       platform name (current configuration)
#     CND_ARTIFACT_DIR_${CONF}   directory of build artifact (current configuration)
#     CND_ARTIFACT_NAME_${CONF}  name of build artifact (current configuration)
#     CND_ARTIFACT_PATH_${CONF}  path to build artifact (current configuration)
#     CND_PACKAGE_DIR_${CONF}    directory of package (current configuration)
#     CND_PACKAGE_NAME_${CONF}   name of package (current configuration)
#     CND_PACKAGE_PATH_${CONF}   path to package (current configuration)
#
# NOCDDL


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
TP=tp1
PRUEBA1=test_15_segundos
PRUEBA2=test_30_segundos
PRUEBA3=test_aleatorio
PRUEBA4=test_completo
PRUEBA5=test_sin_links
PRUEBA6=test_trivial
PRUEBAS= ${PRUEBA1} ${PRUEBA2} ${PRUEBA3} ${PRUEBA4} ${PRUEBA5} ${PRUEBA6}

# build
build: .build-post

.build-pre:
# Add your pre 'build' code here...

.build-post: .build-impl .tp
# Add your post 'build' code here...


# clean
clean: .clean-post

.clean-pre:
# Add your pre 'clean' code here...

.clean-post: .clean-impl .rm_out
	rm -f ${TP}


# clobber
clobber: .clobber-post

.clobber-pre:
# Add your pre 'clobber' code here...

.clobber-post: .clobber-impl
# Add your post 'clobber' code here...


# all
all: .all-post

.all-pre:
# Add your pre 'all' code here...

.all-post: .all-impl .tp
# Add your post 'all' code here...


# build tests
build-tests: .build-tests-post

.build-tests-pre:
# Add your pre 'build-tests' code here...

.build-tests-post: .build-tests-impl .tp
# Add your post 'build-tests' code here...


# run tests
test: .test-post

.test-pre: build-tests
# Add your pre 'test' code here...

.test-post: .test-impl
# Add your post 'test' code here...


# help
help: .help-post

.help-pre:
# Add your pre 'help' code here...

.help-post: .help-impl
# Add your post 'help' code here...

.rm_out:
	rm -f tests_tp1/*.out

.tp:
	cp ${CND_ARTIFACT_PATH_Release} ${TP}

pruebas: .tp .${PRUEBA1} .${PRUEBA2} .${PRUEBA3} .${PRUEBA4} .${PRUEBA5} .${PRUEBA6}
	echo "Todas las pruebas correctas";

.${PRUEBA1}:
	./${TP} tests_tp1/${PRUEBA1}.txt 0.9
	diff tests_tp1/${PRUEBA1}.txt.out tests_tp1/${PRUEBA1}.txt.out.expected

.${PRUEBA2}:
	./${TP} tests_tp1/${PRUEBA2}.txt 0.8
	diff tests_tp1/${PRUEBA2}.txt.out tests_tp1/${PRUEBA2}.txt.out.expected

.${PRUEBA3}:
	./${TP} tests_tp1/${PRUEBA3}.txt 0.85
	diff tests_tp1/${PRUEBA3}.txt.out tests_tp1/${PRUEBA3}.txt.out.expected

.${PRUEBA4}:
	./${TP} tests_tp1/${PRUEBA4}.txt 0.5
	diff tests_tp1/${PRUEBA4}.txt.out tests_tp1/${PRUEBA4}.txt.out.expected

.${PRUEBA5}:
	./${TP} tests_tp1/${PRUEBA5}.txt 0.64
	diff tests_tp1/${PRUEBA5}.txt.out tests_tp1/${PRUEBA5}.txt.out.expected

.${PRUEBA6}:
	./${TP} tests_tp1/${PRUEBA6}.txt 0.3
	diff tests_tp1/${PRUEBA6}.txt.out tests_tp1/${PRUEBA6}.txt.out.expected



# include project implementation makefile
include nbproject/Makefile-impl.mk

# include project make variables
include nbproject/Makefile-variables.mk
