/*
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVUTIL_ATTRIBUTES_INTERNAL_H
#define AVUTIL_ATTRIBUTES_INTERNAL_H

#include "config.h"
#include "attributes.h"

#if (AV_GCC_VERSION_AT_LEAST(4,0) || defined(__clang__)) && (defined(__ELF__) || defined(__MACH__))
#    define attribute_visibility_hidden __attribute__((visibility("hidden")))
#    define FF_VISIBILITY_PUSH_HIDDEN   _Pragma("GCC visibility push(hidden)")
#    define FF_VISIBILITY_POP_HIDDEN    _Pragma("GCC visibility pop")
#else
#    define attribute_visibility_hidden
#    define FF_VISIBILITY_PUSH_HIDDEN
#    define FF_VISIBILITY_POP_HIDDEN
#endif

/**
 * Some globals defined in C files are used from hardcoded asm that assumes small
 * code model (that is, accessing these globals without GOT). This is a problem
 * when FFMpeg is built with medium code model (-mcmodel=medium) which allocates
 * all globals in a data section that's unreachable with PC relative instructions
 * (small code model instruction sequence). We mark all such globals with this
 * attribute_mcmodel_small to ensure assembly accessible globals continue to be
 * allocated in sections reachable from PC relative instructions.
 */
#if ARCH_X86_64 && defined(__ELF__) && AV_HAS_ATTRIBUTE(model)
#    define attribute_mcmodel_small __attribute__(model("small"))
#else
#    define attribute_mcmodel_small
#endif

#endif /* AVUTIL_ATTRIBUTES_INTERNAL_H */
