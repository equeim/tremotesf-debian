# SPDX-FileCopyrightText: 2015-2023 Alexey Rochev
#
# SPDX-License-Identifier: CC0-1.0

find_package(Qt${TREMOTESF_QT_VERSION_MAJOR} ${TREMOTESF_MINIMUM_QT_VERSION} REQUIRED COMPONENTS LinguistTools)
# Make sure to also change translations.qrc
qt_add_translation(qm_files
    en.ts
    es.ts
    fr.ts
    it_IT.ts
    nl_BE.ts
    nl.ts
    pl.ts
    ru.ts
    zh_CN.ts
)
add_custom_target(translations ALL DEPENDS ${qm_files})

configure_file(translations.qrc "${CMAKE_BINARY_DIR}" COPYONLY)
list(APPEND QRC_FILES "${CMAKE_BINARY_DIR}/translations.qrc")
set(QRC_FILES ${QRC_FILES} PARENT_SCOPE)

set(TREMOTESF_QT_TRANSLATIONS_FILENAME "qt")

if (WIN32)
    set(TREMOTESF_BUNDLED_QT_TRANSLATIONS_DIR "translations")
    set(TREMOTESF_BUNDLED_QT_TRANSLATIONS_DIR ${TREMOTESF_BUNDLED_QT_TRANSLATIONS_DIR} PARENT_SCOPE)

    # When we are building with dynamic Qt, we can use windeployqt which will automatically
    # merge all Qt translations in qt_*.qm and install with executable
    # When we are building with static Qt, windeployqt does not work
    # We then need to install translations ourselves, and since they are not merged
    # we install only qtbase_*.qm

    get_target_property(library_type Qt${TREMOTESF_QT_VERSION_MAJOR}::Core TYPE)
    if (library_type STREQUAL "STATIC_LIBRARY")
        message(STATUS "Building with static Qt, attempting to deploy Qt translations")
        if (TREMOTESF_QT6)
            find_file(qt_translations_dir "translations/Qt6")
        else()
            find_file(qt_translations_dir "share/qt5/translations")
        endif()
        if (qt_translations_dir)
            message(STATUS "Deploying Qt translations from ${qt_translations_dir}")
            set(TREMOTESF_QT_TRANSLATIONS_FILENAME "qtbase")
            install(DIRECTORY "${qt_translations_dir}/" DESTINATION "${TREMOTESF_BUNDLED_QT_TRANSLATIONS_DIR}" FILES_MATCHING PATTERN "${TREMOTESF_QT_TRANSLATIONS_FILENAME}_*.qm")
        else()
            message(WARNING "Qt translations not found")
        endif()
    endif()
endif()

set(TREMOTESF_QT_TRANSLATIONS_FILENAME ${TREMOTESF_QT_TRANSLATIONS_FILENAME} PARENT_SCOPE)
