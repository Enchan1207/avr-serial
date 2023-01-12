//
// PROGMEMユーティリティ
//
#ifndef _PGMUTIL_H_
#define _PGMUTIL_H_

#include <avr/pgmspace.h>

/**
 * @brief ROM上に配置された文字列を表すクラス
 */
class FlashString;

/**
 * @brief 引数で渡された文字列リテラルをflashに配置するマクロ
 */
#define F(str) (reinterpret_cast<const FlashString*>(PSTR(str)))

#endif
