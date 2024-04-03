/**
 * @file    psdd4ccm_logger_export.h
 * @author  Martin Corino
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef PSDD4CCM_LOGGER_EXPORT_H
#define PSDD4CCM_LOGGER_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (PSDD4CCM_LOGGER_HAS_DLL)
#  define PSDD4CCM_LOGGER_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && PSDD4CCM_LOGGER_HAS_DLL */

#if !defined (PSDD4CCM_LOGGER_HAS_DLL)
#  define PSDD4CCM_LOGGER_HAS_DLL 1
#endif /* ! PSDD4CCM_LOGGER_HAS_DLL */

#if defined (PSDD4CCM_LOGGER_HAS_DLL) && (PSDD4CCM_LOGGER_HAS_DLL == 1)
#  if defined (PSDD4CCM_LOGGER_BUILD_DLL)
#    define PSDD4CCM_Logger_Export ACE_Proper_Export_Flag
#    define PSDD4CCM_LOGGER_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define PSDD4CCM_LOGGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* PSDD4CCM_LOGGER_BUILD_DLL */
#    define PSDD4CCM_Logger_Export ACE_Proper_Import_Flag
#    define PSDD4CCM_LOGGER_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define PSDD4CCM_LOGGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* PSDD4CCM_LOGGER_BUILD_DLL */
#else /* PSDD4CCM_LOGGER_HAS_DLL == 1 */
#  define PSDD4CCM_Logger_Export
#  define PSDD4CCM_LOGGER_SINGLETON_DECLARATION(T)
#  define PSDD4CCM_LOGGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* PSDD4CCM_LOGGER_HAS_DLL == 1 */

#endif /* PSDD4CCM_LOGGER_EXPORT_H */

// End of auto generated file.
