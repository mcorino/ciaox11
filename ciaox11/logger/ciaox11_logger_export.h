/**
 * @file    ciaox11_logger_export.h
 * @author  Unknown
 *
 * @copyright Copyright (c) Remedy IT Expertise BV
 */
#ifndef CIAOX11_LOGGER_EXPORT_H
#define CIAOX11_LOGGER_EXPORT_H

#include "tao/x11/taox11_export_macros.h"

#if defined (TAOX11_AS_STATIC_LIBS) && !defined (CIAOX11_LOGGER_HAS_DLL)
#  define CIAOX11_LOGGER_HAS_DLL 0
#endif /* TAOX11_AS_STATIC_LIBS && CIAOX11_LOGGER_HAS_DLL */

#if !defined (CIAOX11_LOGGER_HAS_DLL)
#  define CIAOX11_LOGGER_HAS_DLL 1
#endif /* ! CIAOX11_LOGGER_HAS_DLL */

#if defined (CIAOX11_LOGGER_HAS_DLL) && (CIAOX11_LOGGER_HAS_DLL == 1)
#  if defined (CIAOX11_LOGGER_BUILD_DLL)
#    define CIAOX11_Logger_Export TAOX11_Proper_Export_Flag
#    define CIAOX11_LOGGER_SINGLETON_DECLARATION(T) TAOX11_EXPORT_SINGLETON_DECLARATION (T)
#    define CIAOX11_LOGGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) TAOX11_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* CIAOX11_LOGGER_BUILD_DLL */
#    define CIAOX11_Logger_Export TAOX11_Proper_Import_Flag
#    define CIAOX11_LOGGER_SINGLETON_DECLARATION(T) TAOX11_IMPORT_SINGLETON_DECLARATION (T)
#    define CIAOX11_LOGGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) TAOX11_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* CIAOX11_LOGGER_BUILD_DLL */
#else /* CIAOX11_LOGGER_HAS_DLL == 1 */
#  define CIAOX11_Logger_Export
#  define CIAOX11_LOGGER_SINGLETON_DECLARATION(T)
#  define CIAOX11_LOGGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* CIAOX11_LOGGER_HAS_DLL == 1 */

#endif /* CIAOX11_LOGGER_EXPORT_H */

