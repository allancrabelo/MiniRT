#ifndef ERROR_H
# define ERROR_H

// Parsing
# define ERR_USAGE				100
# define ERR_EXTENSION			101
# define ERR_FILE_OPEN			102
# define ERR_FILE_READ			103
# define ERR_FILE_EMPTY			104
# define ERR_INVALID_ELEMENT	105
# define ERR_INVALID_FORMAT		106
# define ERR_INVALID_RANGE		107
# define ERR_DUPLICATE_PARAM	108
# define ERR_MALLOC				109

// Elements
# define ERR_INVALID_PARAM		200
# define ERR_RESOLUTION_PARAM	201
# define ERR_OVER_AMBIENTS		202
# define ERR_AMBIENT_PARAM		203
# define ERR_INVALID_COLOR		204
# define ERR_OVER_CAMERAS		205
# define ERR_CAMERA_PARAM		206
# define ERR_INVALID_COORD		207
# define ERR_INVALID_ORIENT		208
# define ERR_LIGHT_PARAM		209

// MLX
# define ERR_MLX_INIT			300
# define ERR_MLX_WIN			301
# define ERR_MLX_IMG			302
// Type
# define ERR_NOT_FLOAT			401
# define ERR_NOT_ULONG			402

#endif
