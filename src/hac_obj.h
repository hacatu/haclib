/**
 * @file hac_obj.h
 * @brief Macros and functions for emulating objects.
 */
#ifndef __HAC_OBJ__
#define __HAC_OBJ__

#define HAC_O_CALL(self, method, args...) ((self)->method((self), ## args))

#endif

