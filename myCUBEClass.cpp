/*
Name    : myCUBEClass.cpp
Project : LED CUBE 16x8x8 (8x8x8 RED & 8x8x8 GREEN)
Version : 1.0
Date    : 03.06.2018
Author  : tuenhidiy
Email   : tuenhi.n2012@gmail.com
*/

#include <Arduino.h>
#include "myCUBEClass.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

byte Exclamation[][2]   = {{2, 0},{3, 0},{4, 1},{3, 1},{2, 1},{1, 1},{1, 2},{2, 2},{3, 2},{4, 2},{3, 3},{2, 3},{2, 4},{3, 4},{3, 6},{2, 6}}; // !
byte Quotation[][2]     = {{1, 0},{2, 0},{1, 1},{2, 1},{1, 2},{2, 2},{4, 2},{5, 2},{5, 1},{4, 1},{4, 0},{5, 0}}; // "
byte Number[][2]        = {{1, 0},{2, 0},{2, 1},{1, 1},{1, 2},{2, 2},{2, 3},{1, 3},{1, 4},{2, 4},{2, 5},{1, 5},{1, 6},{2, 6},{4, 0},{5, 0},{5, 1},{4, 1},{4, 2},{5, 2},{5, 3},{4, 3},{4, 4},{5, 4},{5, 5},{4, 5},{4, 6},{5, 6},{0, 2},{3, 2},{6, 2},{0, 4},{3, 4},{6, 4}}; // #
byte Dollar[][2]        = {{5, 1},{4, 1},{3, 1},{3, 0},{2, 0},{2, 1},{1, 1},{0, 2},{1, 2},{1, 3},{2, 3},{3, 3},{4, 3},{5, 4},{4, 4},{4, 5},{3, 5},{3, 6},{2, 6},{2, 5},{1, 5},{0, 5}}; // $
byte Percent[][2]       = {{0, 1},{1, 1},{1, 2},{0, 2},{5, 5},{6, 5},{6, 6},{5, 6},{6, 1},{5, 1},{5, 2},{4, 2},{4, 3},{3, 3},{3, 4},{2, 4},{2, 5},{1, 5},{1, 6},{0, 6}}; // %
byte Ampersand[][2]     = {{6, 3},{5, 3},{5, 4},{4, 5},{3, 6},{2, 6},{1, 6},{1, 5},{0, 5},{1, 4},{0, 4},{1, 3},{2, 3},{3, 2},{4, 2},{5, 1},{4, 1},{4, 0},{3, 0},{2, 0},{1, 1},{2, 1},{2, 2},{3, 3},{3, 4},{4, 4},{5, 5},{5, 6},{6, 6}}; // &
byte Apostrophe[][2]    = {{2, 0},{2, 1},{1, 0},{1, 1},{1, 2},{0, 2}}; // '
byte Parentheses1[][2]  = {{4, 0},{3, 0},{3, 1},{2, 1},{2, 2},{1, 2},{1, 3},{2, 3},{2, 4},{1, 4},{2, 5},{3, 5},{3, 6},{4, 6}}; // (
byte Parentheses2[][2]  = {{1, 0},{2, 0},{2, 1},{3, 1},{3, 2},{4, 2},{4, 3},{3, 3},{4, 4},{3, 4},{3, 5},{2, 5},{2, 6},{1, 6}}; // )
byte Asterisk[][2]      = {{6, 1},{5, 1},{5, 2},{4, 2},{3, 4},{2, 4},{2, 5},{1, 5},{1, 1},{2, 1},{2, 2},{3, 2},{4, 4},{5, 4},{5, 5},{6, 5},{0, 3},{1, 3},{2, 3},{3, 3},{4, 3},{5, 3},{6, 3},{7, 3}}; // *
byte Plus[][2]          = {{2, 1},{3, 1},{3, 2},{2, 2},{2, 3},{3, 3},{3, 4},{2, 4},{2, 5},{3, 5},{0, 3},{1, 3},{4, 3},{5, 3}}; // +
byte Comma[][2]         = {{1, 5},{2, 5},{3, 5},{3, 6},{2, 6},{2, 7},{1, 7}}; // ,
byte Hyphen[][2]        = {{0, 3},{1, 3},{2, 3},{3, 3},{4, 3},{5, 3}}; // -
byte Dot[][2]           = {{2, 5},{3, 5},{3, 6},{2, 6}}; // .
byte Slash[][2]         = {{6, 0},{5, 0},{5, 1},{4, 1},{4, 2},{3, 2},{3, 3},{2, 3},{2, 4},{1, 4},{1, 5},{0, 5},{0, 6}}; // /
byte Zero[][2]          = {{4, 0},{3, 0},{2, 0},{1, 0},{0, 1},{1, 1},{1, 2},{0, 2},{0, 3},{1, 3},{1, 4},{0, 4},{0, 5},{1, 5},{1, 6},{2, 6},{3, 6},{4, 6},{4, 5},{5, 5},{5, 4},{4, 4},{4, 3},{5, 3},{5, 2},{4, 2},{5, 1},{4, 1},{3, 2},{3, 3},{2, 3},{2, 4}}; // 0
byte One[][2]           = {{0, 1},{1, 1},{2, 0},{3, 0},{3, 1},{2, 1},{2, 2},{3, 2},{3, 3},{2, 3},{2, 4},{3, 4},{3, 5},{2, 5},{0, 6},{1, 6},{2, 6},{3, 6},{4, 6},{5, 6}}; // 1
byte Two[][2]           = {{1, 1},{0, 1},{1, 0},{2, 0},{3, 0},{4, 0},{5, 1},{4, 1},{4, 2},{5, 2},{4, 3},{3, 3},{2, 3},{2, 4},{1, 4},{1, 5},{0, 5},{0, 6},{1, 6},{2, 6},{3, 6},{4, 6},{5, 6},{5, 5},{4, 5}}; // 2
byte Three[][2]         = {{0, 1},{1, 1},{1, 0},{2, 0},{3, 0},{4, 0},{5, 1},{4, 1},{5, 2},{4, 2},{2, 3},{3, 3},{4, 3},{5, 4},{4, 4},{5, 5},{4, 5},{4, 6},{3, 6},{2, 6},{1, 6},{1, 5},{0, 5}}; // 3
byte Four[][2]          = {{3, 0},{3, 1},{2, 1},{2, 2},{1, 2},{1, 3},{0, 3},{0, 4},{1, 4},{2, 4},{3, 4},{6, 4},{4, 0},{5, 0},{5, 1},{4, 1},{4, 2},{5, 2},{4, 3},{5, 3},{4, 4},{5, 4},{4, 5},{5, 5},{4, 6},{5, 6}}; // 4
byte Five[][2]          = {{5, 0},{4, 0},{3, 0},{2, 0},{1, 0},{0, 0},{0, 1},{1, 1},{0, 2},{1, 2},{2, 2},{3, 2},{4, 2},{5, 3},{4, 3},{4, 4},{5, 4},{5, 5},{4, 5},{4, 6},{3, 6},{2, 6},{1, 6},{1, 5},{0, 5}}; // 5
byte Six[][2]           = {{4, 0},{3, 0},{2, 0},{2, 1},{1, 1},{0, 2},{1, 2},{1, 3},{0, 3},{0, 4},{1, 4},{1, 5},{0, 5},{1, 6},{2, 6},{3, 6},{4, 6},{4, 5},{5, 5},{5, 4},{4, 4},{4, 3},{3, 3},{2, 3}}; // 6
byte Seven[][2]         = {{0, 1},{1, 1},{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{4, 1},{5, 1},{5, 2},{4, 2},{4, 3},{3, 3},{3, 4},{2, 4},{1, 5},{2, 5},{2, 6},{1, 6}}; // 7
byte Eight[][2]         = {{4, 2},{5, 2},{5, 1},{4, 1},{4, 0},{3, 0},{2, 0},{1, 0},{1, 1},{0, 1},{0, 2},{1, 2},{1, 3},{2, 3},{3, 3},{4, 3},{4, 4},{5, 4},{5, 5},{4, 5},{4, 6},{3, 6},{2, 6},{1, 6},{1, 5},{0, 5},{0, 4},{1, 4}}; // 8
byte Nine[][2]          = {{3, 3},{2, 3},{1, 3},{1, 2},{0, 2},{0, 1},{1, 1},{1, 0},{2, 0},{3, 0},{4, 0},{4, 1},{5, 1},{5, 2},{4, 2},{4, 3},{5, 3},{5, 4},{4, 4},{4, 5},{3, 5},{3, 6},{2, 6},{1, 6}}; // 9
byte Colon[][2]         = {{2, 2},{3, 2},{3, 3},{2, 3},{2, 5},{3, 5},{3, 6},{2, 6}}; // :
byte Semicolon[][2]     = {{2, 2},{3, 2},{3, 3},{2, 3},{1, 5},{2, 5},{3, 5},{3, 6},{2, 6},{2, 7},{1, 7}}; // ;
byte Less[][2]          = {{4, 0},{3, 0},{3, 1},{2, 1},{2, 2},{1, 2},{0, 3},{1, 3},{1, 4},{2, 4},{2, 5},{3, 5},{3, 6},{4, 6}}; // <
byte Equals[][2]        = {{0, 2},{1, 2},{2, 2},{3, 2},{4, 2},{5, 2},{0, 4},{1, 4},{2, 4},{3, 4},{4, 4},{5, 4}}; // =
byte Greater[][2]       = {{1, 0},{2, 0},{2, 1},{3, 1},{3, 2},{4, 2},{5, 3},{4, 3},{4, 4},{3, 4},{3, 5},{2, 5},{2, 6},{1, 6}}; // >
byte Question[][2]      = {{0, 1},{1, 1},{1, 0},{2, 0},{3, 0},{4, 0},{5, 1},{4, 1},{4, 2},{5, 2},{4, 3},{3, 3},{3, 4},{2, 4},{2, 6},{3, 6}}; // ?
byte ATsign[][2]        = {{3, 4},{3, 3},{3, 2},{4, 2},{4, 3},{4, 4},{5, 4},{6, 4},{6, 3},{5, 3},{5, 2},{6, 2},{6, 1},{5, 1},{5, 0},{4, 0},{3, 0},{2, 0},{1, 0},{0, 1},{1, 1},{1, 2},{0, 2},{0, 3},{1, 3},{1, 4},{0, 4},{0, 5},{1, 5},{1, 6},{2, 6},{3, 6},{4, 6}}; // @
byte Capital_A[][2]     = {{1, 6},{0, 6},{0, 5},{1, 5},{1, 4},{0, 4},{0, 3},{1, 3},{1, 2},{0, 2},{1, 1},{2, 1},{2, 0},{3, 0},{3, 1},{4, 1},{4, 2},{5, 2},{5, 3},{4, 3},{4, 4},{5, 4},{5, 5},{4, 5},{4, 6},{5, 6},{2, 4},{3, 4}}; // A
byte Capital_B[][2]     = {{0, 6},{1, 6},{2, 6},{2, 5},{1, 5},{1, 4},{2, 4},{2, 3},{1, 3},{1, 2},{2, 2},{2, 1},{1, 1},{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{5, 1},{6, 1},{6, 2},{5, 2},{4, 3},{3, 3},{5, 3},{5, 4},{6, 4},{6, 5},{5, 5},{5, 6},{4, 6},{3, 6}}; // B
byte Capital_C[][2]     = {{6, 1},{5, 1},{5, 0},{4, 0},{3, 0},{2, 0},{2, 1},{1, 1},{1, 2},{0, 2},{0, 3},{1, 3},{1, 4},{0, 4},{1, 5},{2, 5},{2, 6},{3, 6},{4, 6},{5, 6},{5, 5},{6, 5}}; // C
byte Capital_D[][2]     = {{3, 0},{4, 1},{4, 0},{5, 0},{5, 1},{6, 2},{5, 2},{5, 3},{6, 3},{6, 4},{5, 4},{4, 5},{5, 5},{5, 6},{4, 6},{3, 6},{1, 0},{2, 0},{2, 1},{1, 1},{1, 2},{2, 2},{2, 3},{1, 3},{1, 4},{2, 4},{2, 5},{1, 5},{2, 6},{1, 6},{0, 6}}; // D
byte Capital_E[][2]     = {{6, 1},{6, 0},{5, 0},{4, 0},{3, 0},{2, 0},{1, 0},{1, 1},{2, 1},{2, 2},{1, 2},{1, 3},{2, 3},{2, 4},{1, 4},{2, 5},{1, 5},{0, 6},{1, 6},{2, 6},{3, 6},{4, 6},{5, 6},{6, 6},{6, 5},{3, 3},{4, 2},{4, 3},{4, 4}}; // E
byte Capital_F[][2]     = {{6, 1},{6, 0},{5, 0},{4, 0},{3, 0},{2, 0},{1, 0},{1, 1},{2, 1},{2, 2},{1, 2},{1, 3},{2, 3},{2, 4},{1, 4},{2, 5},{1, 5},{0, 6},{1, 6},{2, 6},{3, 6},{3, 3},{4, 2},{4, 3},{4, 4}}; // F
byte Capital_G[][2]     = {{6, 1},{5, 1},{5, 0},{4, 0},{3, 0},{2, 0},{2, 1},{1, 1},{0, 2},{1, 2},{0, 3},{1, 3},{0, 4},{1, 4},{1, 5},{2, 5},{2, 6},{3, 6},{4, 6},{5, 6},{6, 6},{5, 5},{6, 5},{6, 4},{5, 4},{4, 4}}; // G
byte Capital_H[][2]     = {{0, 0},{1, 0},{0, 1},{1, 1},{0, 2},{1, 2},{0, 3},{1, 3},{0, 4},{1, 4},{0, 5},{1, 5},{0, 6},{1, 6},{4, 0},{5, 0},{4, 1},{5, 1},{4, 2},{5, 2},{4, 3},{5, 3},{4, 4},{5, 4},{4, 5},{5, 5},{4, 6},{5, 6},{2, 3},{3, 3}}; // H
byte Capital_I[][2]     = {{1, 0},{2, 0},{3, 0},{4, 0},{3, 1},{2, 1},{2, 2},{3, 2},{3, 3},{2, 3},{2, 4},{3, 4},{3, 5},{2, 5},{1, 6},{2, 6},{3, 6},{4, 6}}; // I
byte Capital_J[][2]     = {{3, 0},{4, 0},{5, 0},{6, 0},{5, 1},{4, 1},{4, 2},{5, 2},{5, 3},{4, 3},{4, 4},{5, 4},{5, 5},{4, 5},{4, 6},{3, 6},{2, 6},{1, 6},{1, 5},{0, 5},{0, 4},{1, 4}}; // J
byte Capital_K[][2]     = {{2, 0},{1, 0},{1, 1},{2, 1},{2, 2},{1, 2},{1, 3},{2, 3},{2, 4},{1, 4},{1, 5},{2, 5},{2, 6},{1, 6},{0, 6},{6, 1},{6, 0},{5, 0},{5, 1},{5, 2},{4, 2},{4, 3},{3, 3},{4, 4},{5, 4},{5, 5},{6, 5},{6, 6},{5, 6}}; // K
byte Capital_L[][2]     = {{3, 0},{2, 0},{1, 0},{1, 1},{2, 1},{2, 2},{1, 2},{1, 3},{2, 3},{2, 4},{1, 4},{1, 5},{0, 6},{1, 6},{2, 5},{2, 6},{3, 6},{4, 6},{5, 6},{5, 5},{6, 6},{6, 5},{6, 4}}; // L
byte Capital_M[][2]     = {{1, 6},{0, 6},{0, 5},{1, 5},{1, 4},{0, 4},{0, 3},{1, 3},{1, 2},{0, 2},{1, 1},{0, 1},{0, 0},{1, 0},{2, 1},{2, 2},{3, 3},{3, 2},{4, 2},{4, 1},{5, 0},{6, 0},{6, 1},{5, 1},{5, 2},{6, 2},{6, 3},{5, 3},{5, 4},{6, 4},{6, 5},{5, 5},{5, 6},{6, 6}}; // M
byte Capital_N[][2]     = {{0, 6},{1, 6},{1, 5},{0, 5},{0, 4},{1, 4},{1, 3},{0, 3},{0, 2},{1, 2},{1, 1},{0, 1},{0, 0},{1, 0},{2, 1},{2, 2},{3, 2},{3, 3},{4, 3},{4, 4},{5, 5},{5, 6},{6, 6},{6, 5},{6, 4},{5, 4},{5, 3},{6, 3},{6, 2},{5, 2},{5, 1},{6, 1},{6, 0},{5, 0}}; // N
byte Capital_O[][2]     = {{4, 1},{4, 0},{3, 0},{2, 0},{2, 1},{1, 1},{0, 2},{1, 2},{1, 3},{0, 3},{0, 4},{1, 4},{1, 5},{2, 5},{2, 6},{3, 6},{4, 6},{4, 5},{5, 5},{5, 4},{6, 4},{6, 3},{5, 3},{6, 2},{5, 2},{5, 1}}; // O
byte Capital_P[][2]     = {{3, 3},{4, 3},{5, 3},{6, 2},{5, 2},{6, 1},{5, 1},{5, 0},{4, 0},{3, 0},{2, 0},{1, 0},{1, 1},{2, 1},{1, 2},{2, 2},{1, 3},{2, 3},{1, 4},{2, 4},{2, 5},{1, 5},{0, 6},{1, 6},{2, 6},{3, 6}}; // P
byte Capital_Q[][2]     = {{4, 4},{5, 4},{5, 3},{4, 3},{4, 2},{5, 2},{5, 1},{4, 1},{4, 0},{3, 0},{2, 0},{1, 0},{0, 1},{1, 1},{1, 2},{0, 2},{0, 3},{1, 3},{1, 4},{0, 4},{1, 5},{2, 5},{3, 4},{3, 5},{4, 5},{3, 6},{4, 6},{5, 6}}; // Q
byte Capital_R[][2]     = {{0, 6},{1, 6},{2, 6},{2, 5},{1, 5},{1, 4},{2, 4},{2, 3},{1, 3},{1, 2},{2, 2},{2, 1},{1, 1},{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 1},{5, 1},{6, 2},{5, 2},{5, 3},{4, 3},{3, 3},{3, 4},{4, 4},{4, 5},{5, 5},{5, 6},{6, 6}}; // R
byte Capital_S[][2]     = {{5, 1},{4, 1},{4, 0},{3, 0},{2, 0},{1, 0},{0, 1},{1, 1},{0, 2},{1, 2},{2, 2},{2, 3},{3, 3},{3, 4},{4, 3},{4, 4},{5, 4},{5, 5},{4, 5},{4, 6},{3, 6},{2, 6},{1, 6},{1, 5},{0, 5}}; // S
byte Capital_T[][2]     = {{0, 1},{0, 0},{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{5, 1},{2, 1},{3, 1},{2, 2},{3, 2},{2, 3},{3, 3},{2, 4},{3, 4},{3, 5},{2, 5},{1, 6},{2, 6},{3, 6},{4, 6}}; // T
byte Capital_U[][2]     = {{0, 0},{1, 0},{0, 1},{1, 1},{0, 2},{1, 2},{0, 3},{1, 3},{0, 4},{1, 4},{0, 5},{1, 5},{0, 6},{1, 6},{2, 6},{3, 6},{4, 6},{5, 6},{5, 5},{4, 5},{4, 4},{5, 4},{5, 3},{4, 3},{4, 2},{5, 2},{5, 1},{4, 1},{4, 0},{5, 0}}; // U
byte Capital_V[][2]     = {{0, 0},{1, 0},{0, 1},{1, 1},{0, 2},{1, 2},{0, 3},{1, 3},{0, 4},{1, 4},{1, 5},{2, 5},{2, 6},{3, 6},{3, 5},{4, 5},{4, 4},{5, 4},{5, 3},{4, 3},{4, 2},{5, 2},{5, 1},{4, 1},{4, 0},{5, 0}}; // V
byte Capital_W[][2]     = {{0, 0},{1, 0},{0, 1},{1, 1},{0, 2},{1, 2},{0, 3},{1, 3},{0, 4},{1, 4},{0, 5},{0, 6},{1, 6},{1, 5},{2, 5},{2, 4},{3, 4},{3, 3},{4, 4},{4, 5},{5, 6},{6, 6},{6, 5},{5, 5},{5, 4},{6, 4},{6, 3},{5, 3},{5, 2},{6, 2},{6, 1},{5, 1},{5, 0},{6, 0}}; // W
byte Capital_X[][2]     = {{0, 0},{1, 0},{0, 1},{1, 1},{1, 2},{2, 2},{2, 3},{3, 3},{4, 4},{5, 4},{5, 5},{6, 5},{5, 6},{6, 6},{6, 0},{5, 0},{6, 1},{5, 1},{5, 2},{4, 2},{4, 3},{2, 4},{1, 4},{0, 5},{1, 5},{1, 6},{0, 6}}; // X
byte Capital_Y[][2]     = {{0, 0},{1, 0},{0, 1},{1, 1},{0, 2},{1, 2},{1, 3},{2, 3},{3, 3},{4, 3},{4, 2},{5, 2},{5, 1},{4, 1},{4, 0},{5, 0},{2, 4},{3, 4},{3, 5},{2, 5},{1, 6},{2, 6},{3, 6},{4, 6}}; // Y
byte Capital_Z[][2]     = {{0, 2},{1, 1},{0, 1},{0, 0},{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{5, 1},{4, 1},{4, 2},{3, 2},{3, 3},{2, 3},{2, 4},{1, 4},{1, 5},{0, 5},{0, 6},{1, 6},{2, 6},{3, 6},{4, 6},{5, 6},{6, 6},{6, 5},{5, 5},{6, 4}}; // Z
byte Square1[][2]       = {{4, 0},{3, 0},{2, 0},{1, 0},{1, 1},{2, 1},{2, 2},{1, 2},{1, 3},{2, 3},{2, 4},{1, 4},{1, 5},{2, 5},{1, 6},{2, 6},{3, 6},{4, 6}}; // [
byte Backslash[][2]     = {{1, 0},{1, 1},{2, 1},{2, 2},{3, 2},{3, 3},{4, 3},{4, 4},{5, 4},{5, 5},{6, 5},{6, 6}}; // \ //
byte Square2[][2]       = {{1, 0},{2, 0},{3, 0},{4, 0},{4, 1},{3, 1},{3, 2},{4, 2},{4, 3},{3, 3},{3, 4},{4, 4},{4, 5},{3, 5},{4, 6},{3, 6},{2, 6},{1, 6}}; // ]
byte Caret[][2]         = {{0, 3},{1, 3},{1, 2},{2, 2},{2, 1},{3, 0},{3, 1},{4, 1},{4, 2},{5, 2},{5, 3},{6, 3}}; // ^
byte Understrike[][2]   = {{0, 7},{1, 7},{2, 7},{3, 7},{4, 7},{5, 7}}; // _
byte Grave[][2]         = {{2, 0},{3, 0},{3, 1},{2, 1},{3, 2},{4, 2}}; // `
byte Lowercase_a [][2]  = {{4, 4},{3, 4},{2, 4},{1, 4},{0, 5},{1, 5},{1, 6},{2, 6},{3, 6},{4, 5},{1, 2},{2, 2},{3, 2},{4, 2},{4, 3},{5, 3},{5, 4},{5, 5},{5, 6},{6, 6}}; // a
byte Lowercase_b [][2]  = {{1, 0},{2, 0},{2, 1},{1, 1},{1, 2},{2, 2},{3, 2},{4, 2},{5, 2},{6, 3},{5, 3},{5, 4},{6, 4},{6, 5},{5, 5},{5, 6},{4, 6},{3, 6},{2, 6},{0, 6},{1, 5},{2, 5},{2, 4},{1, 4},{1, 3},{2, 3}}; // b
byte Lowercase_c [][2]  = {{5, 3},{4, 3},{4, 2},{3, 2},{2, 2},{1, 2},{0, 3},{1, 3},{1, 4},{0, 4},{0, 5},{1, 5},{1, 6},{2, 6},{3, 6},{4, 6},{4, 5},{5, 5}}; // c
byte Lowercase_d [][2]  = {{4, 3},{3, 3},{2, 3},{1, 3},{0, 4},{1, 4},{1, 5},{0, 5},{1, 6},{2, 6},{3, 6},{4, 5},{4, 4},{3, 0},{4, 0},{5, 0},{5, 1},{4, 1},{4, 2},{5, 2},{5, 3},{5, 4},{5, 5},{5, 6},{6, 6}}; // d
byte Lowercase_e [][2]  = {{2, 4},{3, 4},{4, 4},{5, 4},{5, 3},{4, 3},{4, 2},{3, 2},{2, 2},{1, 2},{0, 3},{1, 3},{1, 4},{0, 4},{0, 5},{1, 5},{1, 6},{2, 6},{3, 6},{4, 6}}; // e
byte Lowercase_f [][2]  = {{5, 1},{4, 1},{4, 0},{3, 0},{2, 0},{1, 1},{2, 1},{2, 2},{1, 2},{1, 3},{2, 3},{1, 4},{2, 4},{2, 5},{1, 5},{0, 6},{1, 6},{2, 6},{3, 6},{0, 3},{3, 3}}; // f
byte Lowercase_g [][2]  = {{4, 3},{3, 2},{2, 2},{1, 2},{0, 3},{1, 3},{0, 4},{1, 4},{1, 5},{2, 5},{3, 5},{4, 5},{4, 4},{6, 2},{5, 2},{5, 3},{5, 4},{5, 5},{5, 6},{4, 6},{3, 7},{2, 7},{1, 7},{0, 7}}; // g
byte Lowercase_h [][2]  = {{0, 6},{1, 6},{2, 6},{2, 5},{1, 5},{1, 4},{2, 4},{2, 3},{1, 3},{1, 2},{2, 2},{2, 1},{1, 1},{1, 0},{2, 0},{3, 3},{4, 2},{5, 2},{5, 3},{6, 3},{6, 4},{5, 4},{5, 5},{6, 5},{6, 6},{5, 6}}; // h
byte Lowercase_i [][2]  = {{1, 2},{2, 2},{3, 2},{3, 3},{2, 3},{2, 4},{3, 4},{3, 5},{2, 5},{1, 6},{2, 6},{3, 6},{4, 6},{2, 0},{3, 0}}; // i
byte Lowercase_j [][2]  = {{1, 2},{2, 2},{3, 2},{4, 2},{4, 3},{3, 3},{3, 4},{4, 4},{4, 5},{3, 5},{4, 6},{3, 6},{3, 7},{2, 7},{1, 7},{1, 6},{0, 6}}; // j
byte Lowercase_k [][2]  = {{1, 0},{2, 0},{2, 1},{1, 1},{1, 2},{2, 2},{2, 3},{1, 3},{1, 4},{2, 4},{2, 5},{1, 5},{2, 6},{1, 6},{0, 6},{6, 2},{5, 2},{5, 3},{4, 3},{3, 4},{4, 4},{4, 5},{5, 5},{5, 6},{6, 6}}; // k
byte Lowercase_l [][2]  = {{1, 0},{2, 0},{3, 0},{3, 1},{2, 1},{2, 2},{3, 2},{3, 3},{2, 3},{2, 4},{3, 4},{3, 5},{2, 5},{1, 6},{2, 6},{3, 6},{4, 6}}; // l
byte Lowercase_m [][2]  = {{0, 6},{1, 6},{1, 5},{0, 5},{0, 4},{1, 4},{1, 3},{0, 3},{0, 2},{1, 2},{2, 2},{2, 3},{3, 4},{3, 3},{4, 3},{4, 2},{5, 2},{6, 3},{5, 3},{5, 4},{6, 4},{6, 5},{5, 5},{5, 6},{6, 6}}; // m
byte Lowercase_n [][2]  = {{0, 6},{1, 6},{1, 5},{0, 5},{0, 4},{1, 4},{1, 3},{0, 3},{0, 2},{1, 2},{2, 2},{3, 2},{4, 2},{4, 3},{5, 3},{5, 4},{4, 4},{4, 5},{5, 5},{5, 6},{4, 6}}; // n
byte Lowercase_o [][2]  = {{4, 2},{3, 2},{2, 2},{1, 2},{0, 3},{1, 3},{1, 4},{0, 4},{0, 5},{1, 5},{1, 6},{2, 6},{3, 6},{4, 6},{4, 5},{5, 5},{5, 4},{4, 4},{4, 3},{5, 3}}; // o
byte Lowercase_p [][2]  = {{2, 4},{2, 3},{3, 2},{4, 2},{5, 2},{6, 3},{5, 3},{5, 4},{6, 4},{5, 5},{4, 5},{3, 5},{2, 5},{0, 2},{1, 2},{1, 3},{1, 4},{1, 5},{2, 6},{1, 6},{0, 7},{1, 7},{2, 7},{3, 7}}; // p
byte Lowercase_q [][2]  = {{6, 2},{5, 2},{4, 3},{3, 2},{2, 2},{1, 2},{0, 3},{1, 3},{1, 4},{0, 4},{1, 5},{2, 5},{3, 5},{4, 5},{4, 4},{5, 3},{5, 4},{5, 5},{5, 6},{4, 6},{3, 7},{6, 7}}; // q
byte Lowercase_r [][2]  = {{0, 2},{1, 2},{1, 3},{1, 4},{1, 5},{0, 6},{1, 6},{2, 6},{3, 6},{2, 5},{2, 4},{2, 3},{3, 2},{4, 2},{4, 3},{5, 3},{5, 4},{4, 4}}; // r
byte Lowercase_s [][2]  = {{5, 2},{4, 2},{3, 2},{2, 2},{1, 2},{0, 3},{1, 3},{1, 4},{2, 4},{3, 4},{4, 4},{5, 5},{4, 5},{4, 6},{3, 6},{2, 6},{1, 6},{0, 6}}; // s
byte Lowercase_t [][2]  = {{3, 0},{2, 1},{3, 1},{3, 2},{2, 2},{2, 3},{3, 3},{3, 4},{2, 4},{2, 5},{3, 5},{3, 6},{4, 6},{5, 5},{1, 2},{4, 2},{5, 2}}; // t
byte Lowercase_u [][2]  = {{0, 2},{1, 2},{1, 3},{0, 3},{0, 4},{1, 4},{1, 5},{0, 5},{1, 6},{2, 6},{3, 6},{4, 5},{4, 4},{4, 3},{4, 2},{5, 2},{5, 3},{5, 4},{5, 5},{5, 6},{6, 6}}; // u
byte Lowercase_v [][2]  = {{0, 2},{1, 2},{1, 3},{0, 3},{0, 4},{1, 4},{1, 5},{2, 5},{2, 6},{3, 6},{3, 5},{4, 5},{4, 4},{5, 4},{5, 3},{4, 3},{4, 2},{5, 2}}; // v
byte Lowercase_w [][2]  = {{0, 2},{1, 2},{1, 3},{0, 3},{0, 4},{1, 4},{1, 5},{0, 5},{1, 6},{2, 6},{2, 5},{3, 4},{3, 5},{4, 5},{4, 6},{5, 6},{5, 5},{6, 5},{6, 4},{5, 4},{5, 3},{6, 3},{6, 2},{5, 2}}; // w
byte Lowercase_x [][2]  = {{0, 2},{1, 2},{1, 3},{2, 3},{2, 4},{4, 5},{5, 5},{5, 6},{6, 6},{6, 2},{5, 2},{5, 3},{4, 3},{4, 4},{3, 4},{2, 5},{1, 5},{1, 6},{0, 6}}; // x
byte Lowercase_y [][2]  = {{0, 2},{1, 2},{1, 3},{0, 3},{0, 4},{1, 4},{1, 5},{2, 5},{3, 5},{4, 5},{4, 4},{4, 3},{4, 2},{5, 2},{5, 3},{5, 4},{5, 5},{5, 6},{4, 6},{3, 7},{2, 7},{1, 7},{0, 7}}; // y
byte Lowercase_z [][2]  = {{0, 3},{0, 2},{1, 2},{2, 2},{3, 2},{4, 2},{5, 2},{4, 3},{3, 3},{3, 4},{2, 4},{2, 5},{1, 5},{0, 6},{1, 6},{2, 6},{3, 6},{4, 6},{5, 6},{5, 5}}; // z
byte Braces1[][2]       = {{5, 0},{4, 0},{3, 0},{2, 1},{3, 1},{3, 2},{2, 2},{0, 3},{1, 3},{2, 3},{2, 4},{3, 4},{2, 5},{3, 5},{3, 6},{4, 6},{5, 6}}; // {
byte Vbar[][2]          = {{3, 0},{4, 0},{4, 1},{3, 1},{3, 2},{4, 2},{4, 4},{3, 4},{3, 5},{4, 5},{4, 6},{3, 6}}; // |
byte Braces2[][2]       = {{0, 0},{1, 0},{2, 0},{2, 1},{3, 1},{2, 2},{3, 2},{5, 3},{4, 3},{3, 3},{2, 4},{3, 4},{3, 5},{2, 5},{2, 6},{1, 6},{0, 6}}; // }
byte Tilde[][2]         = {{0, 1},{1, 1},{1, 0},{2, 0},{3, 0},{3, 1},{4, 1},{5, 1},{5, 0},{6, 0}}; // ~
byte Delete[][2]        = {{0, 0},{0, 1},{1, 0},{3, 0},{2, 1},{1, 2},{0, 3},{0, 5},{1, 4},{2, 3},{3, 2},{4, 1},{5, 0},{7, 0},{6, 1},{5, 2},{4, 3},{3, 4},{2, 5},{1, 6},{0, 7},{2, 7},{3, 6},{4, 5},{5, 4},{6, 3},{7, 2},{7, 4},{6, 5},{5, 6},{4, 7},{6, 7},{7, 6}}; //

myCUBE::myCUBE()
{

}

// Public Methods //////////////////////////////////////////////////////////////

void myCUBE::Init(uint8_t pinDATA, uint8_t pinCLOCK, 
          uint8_t pinRowA, uint8_t pinRowB, uint8_t pinRowC, uint8_t pinRowD,
          uint8_t pinOE, uint8_t pinSTB)

{
  row = 0;
  pinMode(pinDATA, OUTPUT); 
  pinMode(pinCLOCK, OUTPUT); 
  pinMode(pinRowA, OUTPUT); 
  pinMode(pinRowB, OUTPUT); 
  pinMode(pinRowC, OUTPUT); 
  pinMode(pinRowD, OUTPUT); 
  pinMode(pinOE, OUTPUT); 
  pinMode(pinSTB, OUTPUT); 
  
  bitDATA = digitalPinToBitMask(pinDATA);
  uint8_t portDATA = digitalPinToPort(pinDATA);
  outDATA = portOutputRegister(portDATA);

  bitCLOCK = digitalPinToBitMask(pinCLOCK);
  uint8_t portCLOCK = digitalPinToPort(pinCLOCK);
  outCLOCK = portOutputRegister(portCLOCK);

  bitRowA = digitalPinToBitMask(pinRowA);
  uint8_t portRowA = digitalPinToPort(pinRowA);
  outRowA = portOutputRegister(portRowA);

  bitRowB = digitalPinToBitMask(pinRowB);
  uint8_t portRowB = digitalPinToPort(pinRowB);
  outRowB = portOutputRegister(portRowB);

  bitRowC = digitalPinToBitMask(pinRowC);
  uint8_t portRowC = digitalPinToPort(pinRowC);
  outRowC = portOutputRegister(portRowC);

  bitRowD = digitalPinToBitMask(pinRowD);
  uint8_t portRowD = digitalPinToPort(pinRowD);
  outRowD = portOutputRegister(portRowD);

  bitOE = digitalPinToBitMask(pinOE);
  uint8_t portOE = digitalPinToPort(pinOE);
  outOE = portOutputRegister(portOE);

  bitSTB = digitalPinToBitMask(pinSTB);
  uint8_t portSTB = digitalPinToPort(pinSTB);
  outSTB = portOutputRegister(portSTB);

  fill(0x00); // clear all cube
  Timer1Setup();
}
void myCUBE::delay_ms(uint16_t x)
{
  uint8_t y, z;
  for ( ; x > 0 ; x--){
    for ( y = 0 ; y < 90 ; y++){
      for ( z = 0 ; z < 6 ; z++){
        asm volatile ("nop");
      }
    }
  }
}
// This function validates that we are drawing inside the cube.
unsigned char myCUBE::inrange(int x, int y, int z)
{
  if (x >= 0 && x < CUBE_XSIZE && y >= 0 && y < CUBE_YSIZE && z >= 0 && z < CUBE_ZSIZE)
  {
    return 1;
  } else
  {
    // One of the coordinates was outside the cube.
    return 0;
  }
}
// Set a single voxel to ON
void myCUBE::setvoxel(int x, int y, int z)
{
  if (inrange(x,y,z))
  //{
    //y_T = y & B00000111;
    //z_T = z + (y < 8 ? 0 : 8);
    cube[z + (y < 8 ? 0 : 8)][y & B00000111] |= (1 << x);
  //}
}

// Set a single voxel to OFF
void myCUBE::clrvoxel(int x, int y, int z)
{
  if (inrange(x,y,z))
  
    cube[z + (y < 8 ? 0 : 8)][y & B00000111] &= ~(1 << x);
}

// Fill a value into all 64 byts of the cube buffer
// Mostly used for clearing. fill(0x00)
// or setting all on. fill(0xff)
void myCUBE::fill(unsigned char pattern)
{
  int z;
  int y;
  for (z=0;z<CUBE_ZSIZE;z++)
  {
    for (y=0;y<CUBE_YSIZE;y++)
    {      

      cube[z + (y < 8 ? 0 : 8)][y & B00000111] = pattern;
    }
  }
}

// Set a single voxel in the temporary cube buffer to ON
void myCUBE::tmpsetvoxel(int x, int y, int z)
{
  if (inrange(x,y,z))
  fb[z + (y < 8 ? 0 : 8)][y & B00000111] |= (1 << x);
}


// Set a single voxel to OFF
void myCUBE::tmpclrvoxel(int x, int y, int z)
{
  if (inrange(x,y,z))
  fb[z + (y < 8 ? 0 : 8)][y & B00000111] &= ~(1 << x);
}


// Get the current status of a voxel
unsigned char myCUBE::getvoxel(int x, int y, int z)
{
  if (inrange(x,y,z))
  {
    if (cube[z + (y < 8 ? 0 : 8)][y & B00000111] & (1 << x))
    {
      return 1;
    } else
    {
      return 0;
    }
  } else
  {
    return 0;
  }
}

// In some effect we want to just take bool and write it to a voxel
// this function calls the apropriate voxel manipulation function.
void myCUBE::altervoxel(int x, int y, int z, int state)
{
  if (state == 1)
  {
    setvoxel(x,y,z);
  } else
  {
    clrvoxel(x,y,z);
  }
}

// Flip the state of a voxel.
// If the voxel is 1, its turned into a 0, and vice versa.
void myCUBE::flpvoxel(int x, int y, int z)
{
  if (inrange(x, y, z))   
    cube[z + (y < 8 ? 0 : 8)][y & B00000111] ^= (1 << x);
}


// Sets all voxels along a X/Y plane at a given point
// on axis Z
void myCUBE::setplane_z (int z)
{
  int i;
  if (z>=0 && z<CUBE_ZSIZE)
  {
    for (i=0;i<8;i++)
    {
    cube[z][i] = 0xff;
    cube[z+8][i] = 0xff;
    }
    
  }
}

// Clears voxels in the same manner as above
void myCUBE::clrplane_z (int z)
{
  int i;
  if (z>=0 && z<CUBE_ZSIZE)
  {
    for (i=0;i<8;i++)
    {
      cube[z][i] = 0x00;
      cube[z+8][i] = 0x00;
    }
  }
}

void myCUBE::setplane_x (int x)
{
  int z;
  int y;
  if (x>=0 && x<CUBE_XSIZE)
  {
    for (z=0;z<CUBE_ZSIZE;z++)
    {
      for (y=0;y<CUBE_YSIZE;y++)
      {
        cube[z + (y < 8 ? 0 : 8)][y & B00000111] |= (1 << x);
      }
    }
  }
}

void myCUBE::clrplane_x (int x)
{
  int z;
  int y;
  if (x>=0 && x<CUBE_XSIZE)
  {
    for (z=0;z<CUBE_ZSIZE;z++)
    {
      for (y=0;y<CUBE_YSIZE;y++)
      {
        cube[z + (y < 8 ? 0 : 8)][y & B00000111] &= ~(1 << x);
      }
    }
  }
}

void myCUBE::setplane_y (int y)
{
  int z;
  if (y>=0 && y<CUBE_YSIZE)
  {
    for (z=0;z<CUBE_ZSIZE;z++)
    {      
      cube[z + (y < 8 ? 0 : 8)][y & B00000111] = 0xff;
    }
  } 
}

void myCUBE::clrplane_y (int y)
{
  int z;
  if (y>=0 && y<CUBE_YSIZE)
  {
    for (z=0;z<CUBE_ZSIZE;z++)
    {       
      cube[z + (y < 8 ? 0 : 8)][y & B00000111] = 0x00; 
    }
  }
}

void myCUBE::setplane (char axis, unsigned char i)
{
    switch (axis)
    {
        case AXIS_X:
            setplane_x(i);
            break;
        
       case AXIS_Y:
            setplane_y(i);
            break;

       case AXIS_Z:
            setplane_z(i);
            break;
    }
}

void myCUBE::clrplane (char axis, unsigned char i)
{
    switch (axis)
    {
        case AXIS_X:
            clrplane_x(i);
            break;
        
       case AXIS_Y:
            clrplane_y(i);
            break;

       case AXIS_Z:
            clrplane_z(i);
            break;
    }
}

// Shift the entire contents of the cube along an axis
// This is great for effects where you want to draw something
// on one side of the cube and have it flow towards the other
// side. Like rain flowing down the Z axiz.
void myCUBE::shift (char axis, int direction)
{
  int i, x ,y;
  int ii, iii;
  int state;

  for (i = 0; i < CUBE_ZSIZE; i++)
  {
    if (direction == -1)
    {
      ii = i;
    } else
    {
      ii = (7-i);
    } 
  
  
    for (x = 0; x < CUBE_XSIZE; x++)
    {
      for (y = 0; y < CUBE_YSIZE; y++)
      {
        if (direction == -1)
        {
          iii = ii+1;
        } else
        {
          iii = ii-1;
        }
        
        if (axis == AXIS_Z)
        {
          state = getvoxel(x,y,iii);
          altervoxel(x,y,ii,state);
        }
        
        if (axis == AXIS_Y)
        {
          state = getvoxel(x,iii,y);
          altervoxel(x,ii,y,state);
        }
        
        if (axis == AXIS_X)
        {
          state = getvoxel(iii,y,x);
          altervoxel(ii,y,x,state);
        }
      }
    }
  }
  
  if (direction == -1)
  {
    i = 7;
  } else
  {
    i = 0;
  } 
  
  for (x = 0; x < CUBE_XSIZE; x++)
  {
    for (y = 0; y < CUBE_YSIZE; y++)
    {
      if (axis == AXIS_Z)
        clrvoxel(x,y,i);
        
      if (axis == AXIS_Y)
        clrvoxel(x,i,y);
      
      if (axis == AXIS_X)
        clrvoxel(i,y,x);
    }
  }
}

// Flip the cube 180 degrees along the y axis.
void myCUBE::mirror_y (void)
{
    unsigned char buffer[CUBE_ZSIZE][CUBE_YSIZE];
    unsigned char x,y,z;

    memcpy(buffer, cube, CUBE_BYTES); // copy the current cube into a buffer.

    fill(0x00);
    for (z=0; z<CUBE_ZSIZE; z++)
    {
        for (y=0; y<CUBE_YSIZE; y++)
        {
            for (x=0; x<CUBE_XSIZE; x++)
            {
                if (buffer[z + (y < 8 ? 0 : 8)][y & B00000111] & (0x01 << x))
                    setvoxel(x,CUBE_YSIZE-1-y,z);
            }
        }
    }

}

// Flip the cube 180 degrees along the x axis
void myCUBE::mirror_x (void)
{
    unsigned char buffer[CUBE_ZSIZE][CUBE_YSIZE];
    unsigned char y,z;

    memcpy(buffer, cube, CUBE_BYTES); // copy the current cube into a buffer.

    fill(0x00);
    
    for (z=0; z<CUBE_ZSIZE; z++)
    {
        for (y=0; y<CUBE_YSIZE; y++)
        {
            // This will break with different buffer sizes..
            cube[z + (y < 8 ? 0 : 8)][y & B00000111] = flipbyte(buffer[z + (y < 8 ? 0 : 8)][y & B00000111]);
        }
    }
}

// flip the cube 180 degrees along the z axis
void myCUBE::mirror_z (void)
{
    unsigned char buffer[CUBE_ZSIZE][CUBE_YSIZE];
    unsigned char z, y;

    memcpy(buffer, cube, CUBE_BYTES); // copy the current cube into a buffer.

    for (y=0; y<CUBE_YSIZE; y++)
    {
        for (z=0; z<CUBE_ZSIZE; z++)
        { 
            cube[CUBE_ZSIZE-1-(z + (y < 8 ? 0 : 8))][y & B00000111] = buffer[z + (y < 8 ? 0 : 8)][y & B00000111];
        }
    }
}

void myCUBE::argorder(int ix1, int ix2, int *ox1, int *ox2)
{
  if (ix1>ix2)
  {
    int tmp;
    tmp = ix1;
    ix1= ix2;
    ix2 = tmp;
  }
  *ox1 = ix1;
  *ox2 = ix2;
}

// Returns a byte with a row of 1's drawn in it.
// byteline(2,5) gives 0b00111100
char myCUBE::byteline (int start, int end)
{
  return ((0xff<<start) & ~(0xff<<(end+1)));
}

// Flips a byte 180 degrees.
// MSB becomes LSB, LSB becomes MSB.
char myCUBE::flipbyte (char byte)
{
  char flop = 0x00;

  flop = (flop & 0b11111110) | (0b00000001 & (byte >> 7));
  flop = (flop & 0b11111101) | (0b00000010 & (byte >> 5));
  flop = (flop & 0b11111011) | (0b00000100 & (byte >> 3));
  flop = (flop & 0b11110111) | (0b00001000 & (byte >> 1));
  flop = (flop & 0b11101111) | (0b00010000 & (byte << 1));
  flop = (flop & 0b11011111) | (0b00100000 & (byte << 3));
  flop = (flop & 0b10111111) | (0b01000000 & (byte << 5));
  flop = (flop & 0b01111111) | (0b10000000 & (byte << 7));
  return flop;
}
void myCUBE::tmpfill (unsigned char pattern)
{
  int z;
  int y;
  for (z=0;z<CUBE_ZSIZE;z++)
  {
    for (y=0;y<CUBE_YSIZE;y++)
    {
      fb[z][y] = pattern;
    }
  }
}


// Scroll the outer sides of the cube around an axis by value
void myCUBE::TranslateScroll(char axis, int8_t value)
{
  uint8_t i, j, k, l, x, y, z, prev_x, prev_y, prev_z, dx, dy, dz, start_state1, start_state2;
  int8_t positive, negative;
  int8_t increment_x[4];
  int8_t increment_y[4];
  int8_t increment_z[4];

  positive = (value > 0);
  negative = (value < 0);

  switch (axis)
  {
  default:
  case AXIS_X:
    increment_x[0] = 0;
    increment_x[1] = 0;
    increment_x[2] = 0;
    increment_x[3] = 0;

    increment_y[0] = positive;
    increment_y[1] = negative;
    increment_y[2] = -positive;
    increment_y[3] = -negative;

    increment_z[0] = negative;
    increment_z[1] = positive;
    increment_z[2] = -negative;
    increment_z[3] = -positive;

    dx = 1;
    dy = 0;
    dz = 0;
    break;

  case AXIS_Y:
    increment_x[0] = positive;
    increment_x[1] = negative;
    increment_x[2] = -positive;
    increment_x[3] = -negative;

    increment_y[0] = 0;
    increment_y[1] = 0;
    increment_y[2] = 0;
    increment_y[3] = 0;

    increment_z[0] = negative;
    increment_z[1] = positive;
    increment_z[2] = -negative;
    increment_z[3] = -positive;

    dx = 0;
    dy = 1;
    dz = 0;
    break;

  case AXIS_Z:
    increment_x[0] = negative;
    increment_x[1] = positive;
    increment_x[2] = -negative;
    increment_x[3] = -positive;

    increment_y[0] = positive;
    increment_y[1] = negative;
    increment_y[2] = -positive;
    increment_y[3] = -negative;

    increment_z[0] = 0;
    increment_z[1] = 0;
    increment_z[2] = 0;
    increment_z[3] = 0;

    dx = 0;
    dy = 0;
    dz = 1;
    break;
  }

  value -= ((value >= 0) - 1) & (value << 1);

  for (l = 0; l<value; l++)
  {
    x = 0;
    y = 0;
    z = 0;

    for (i = 0; i < 8; i++)
    {
      start_state1 = getvoxel(x, y, z);
      start_state2 = getvoxel(x, 15-y, z);
      for (j = 0; j < 4; j++)
      {
        for (k = 0; k < 7; k++)
        {
          prev_x = x;
          prev_y = y;
          prev_z = z;

          x += increment_x[j];
          y += increment_y[j];
          z += increment_z[j];

          altervoxel(prev_x, prev_y, prev_z,getvoxel(x, y, z));
          altervoxel(prev_x, 15-prev_y, prev_z,getvoxel(x, 15-y, z));
        }
      }

      altervoxel(prev_x, prev_y, prev_z, start_state1);
      altervoxel(prev_x, 15-prev_y, prev_z, start_state2);
      x += dx;
      y += dy;
      z += dz;
    }
  }
}

void myCUBE::HandwrittenNumber(char axis, byte xyz, byte offset, byte number, bool hwclock)
{

switch (number)
  {

    case '!': DrawDigit(axis, xyz, Exclamation, 16, offset, hwclock); break; //  Hand-writting character ' ! ' //
    case '"': DrawDigit(axis, xyz, Quotation, 12, offset, hwclock); break; //  Hand-writting character ' " ' //
    case '#': DrawDigit(axis, xyz, Number, 34, offset, hwclock); break; //  Hand-writting character ' # ' //
    case '$': DrawDigit(axis, xyz, Dollar, 22, offset, hwclock); break; //  Hand-writting character ' $ ' //
    case '%': DrawDigit(axis, xyz, Percent, 20, offset, hwclock); break; //  Hand-writting character ' % ' //
    case '&': DrawDigit(axis, xyz, Ampersand, 29, offset, hwclock); break; //  Hand-writting character ' & ' //
    //case ''': DrawDigit(axis, xyz, Apostrophe, 6, offset, hwclock); break; //  Hand-writting character ' ' ' //
    case '(': DrawDigit(axis, xyz, Parentheses1, 14, offset, hwclock); break; //  Hand-writting character ' ( ' //
    case ')': DrawDigit(axis, xyz, Parentheses2, 14, offset, hwclock); break; //  Hand-writting character ' ) ' //
    case '*': DrawDigit(axis, xyz, Asterisk, 24, offset, hwclock); break; //  Hand-writting character ' * ' //
    case '+': DrawDigit(axis, xyz, Plus, 14, offset, hwclock); break; //  Hand-writting character ' + ' //
    case ',': DrawDigit(axis, xyz, Comma, 7, offset, hwclock); break; //  Hand-writting character ' , ' //
    case '-': DrawDigit(axis, xyz, Hyphen, 6, offset, hwclock); break; //  Hand-writting character ' - ' //
    case '.': DrawDigit(axis, xyz, Dot, 4, offset, hwclock); break; //  Hand-writting character ' . ' //
    case '/': DrawDigit(axis, xyz, Slash, 13, offset, hwclock); break; //  Hand-writting character ' / ' //
    case 0: DrawDigit(axis, xyz, Zero, 32, offset, hwclock); break; //  Hand-writting character ' 0 ' //
    case 1: DrawDigit(axis, xyz, One, 20, offset, hwclock); break; //  Hand-writting character ' 1 ' //
    case 2: DrawDigit(axis, xyz, Two, 25, offset, hwclock); break; //  Hand-writting character ' 2 ' //
    case 3: DrawDigit(axis, xyz, Three, 23, offset, hwclock); break; //  Hand-writting character ' 3 ' //
    case 4: DrawDigit(axis, xyz, Four, 26, offset, hwclock); break; //  Hand-writting character ' 4 ' //
    case 5: DrawDigit(axis, xyz, Five, 25, offset, hwclock); break; //  Hand-writting character ' 5 ' //
    case 6: DrawDigit(axis, xyz, Six, 24, offset, hwclock); break; //  Hand-writting character ' 6 ' //
    case 7: DrawDigit(axis, xyz, Seven, 19, offset, hwclock); break; //  Hand-writting character ' 7 ' //
    case 8: DrawDigit(axis, xyz, Eight, 28, offset, hwclock); break; //  Hand-writting character ' 8 ' //
    case 9: DrawDigit(axis, xyz, Nine, 24, offset, hwclock); break; //  Hand-writting character ' 9 ' //
    case ':': DrawDigit(axis, xyz, Colon, 8, offset, hwclock); break; //  Hand-writting character ' : ' //
    case ';': DrawDigit(axis, xyz, Semicolon, 11, offset, hwclock); break; //  Hand-writting character ' ; ' //
    case '<': DrawDigit(axis, xyz, Less, 14, offset, hwclock); break; //  Hand-writting character ' < ' //
    case '=': DrawDigit(axis, xyz, Equals, 12, offset, hwclock); break; //  Hand-writting character ' = ' //
    case '>': DrawDigit(axis, xyz, Greater, 14, offset, hwclock); break; //  Hand-writting character ' > ' //
    case '?': DrawDigit(axis, xyz, Question, 16, offset, hwclock); break; //  Hand-writting character ' ? ' //
    case '@': DrawDigit(axis, xyz, ATsign, 33, offset, hwclock); break; //  Hand-writting character ' @ ' //
    case 'A': DrawDigit(axis, xyz, Capital_A, 28, offset, hwclock); break; //  Hand-writting character ' A ' //
    case 'B': DrawDigit(axis, xyz, Capital_B, 32, offset, hwclock); break; //  Hand-writting character ' B ' //
    case 'C': DrawDigit(axis, xyz, Capital_C, 22, offset, hwclock); break; //  Hand-writting character ' C ' //
    case 'D': DrawDigit(axis, xyz, Capital_D, 31, offset, hwclock); break; //  Hand-writting character ' D ' //
    case 'E': DrawDigit(axis, xyz, Capital_E, 29, offset, hwclock); break; //  Hand-writting character ' E ' //
    case 'F': DrawDigit(axis, xyz, Capital_F, 25, offset, hwclock); break; //  Hand-writting character ' F ' //
    case 'G': DrawDigit(axis, xyz, Capital_G, 26, offset, hwclock); break; //  Hand-writting character ' G ' //
    case 'H': DrawDigit(axis, xyz, Capital_H, 30, offset, hwclock); break; //  Hand-writting character ' H ' //
    case 'I': DrawDigit(axis, xyz, Capital_I, 18, offset, hwclock); break; //  Hand-writting character ' I ' //
    case 'J': DrawDigit(axis, xyz, Capital_J, 22, offset, hwclock); break; //  Hand-writting character ' J ' //
    case 'K': DrawDigit(axis, xyz, Capital_K, 29, offset, hwclock); break; //  Hand-writting character ' K ' //
    case 'L': DrawDigit(axis, xyz, Capital_L, 23, offset, hwclock); break; //  Hand-writting character ' L ' //
    case 'M': DrawDigit(axis, xyz, Capital_M, 34, offset, hwclock); break; //  Hand-writting character ' M ' //
    case 'N': DrawDigit(axis, xyz, Capital_N, 34, offset, hwclock); break; //  Hand-writting character ' N ' //
    case 'O': DrawDigit(axis, xyz, Capital_O, 26, offset, hwclock); break; //  Hand-writting character ' O ' //
    case 'P': DrawDigit(axis, xyz, Capital_P, 26, offset, hwclock); break; //  Hand-writting character ' P ' //
    case 'Q': DrawDigit(axis, xyz, Capital_Q, 28, offset, hwclock); break; //  Hand-writting character ' Q ' //
    case 'R': DrawDigit(axis, xyz, Capital_R, 31, offset, hwclock); break; //  Hand-writting character ' R ' //
    case 'S': DrawDigit(axis, xyz, Capital_S, 25, offset, hwclock); break; //  Hand-writting character ' S ' //
    case 'T': DrawDigit(axis, xyz, Capital_T, 22, offset, hwclock); break; //  Hand-writting character ' T ' //
    case 'U': DrawDigit(axis, xyz, Capital_U, 30, offset, hwclock); break; //  Hand-writting character ' U ' //
    case 'V': DrawDigit(axis, xyz, Capital_V, 26, offset, hwclock); break; //  Hand-writting character ' V ' //
    case 'W': DrawDigit(axis, xyz, Capital_W, 34, offset, hwclock); break; //  Hand-writting character ' W ' //
    case 'X': DrawDigit(axis, xyz, Capital_X, 27, offset, hwclock); break; //  Hand-writting character ' X ' //
    case 'Y': DrawDigit(axis, xyz, Capital_Y, 24, offset, hwclock); break; //  Hand-writting character ' Y ' //
    case 'Z': DrawDigit(axis, xyz, Capital_Z, 30, offset, hwclock); break; //  Hand-writting character ' Z ' //
    case '[': DrawDigit(axis, xyz, Square1, 18, offset, hwclock); break; //  Hand-writting character ' [ ' //
    //case '\': DrawDigit(axis, xyz, Backslash, 12, offset, hwclock); break; //  Hand-writting character ' \ ' //
    case ']': DrawDigit(axis, xyz, Square2, 18, offset, hwclock); break; //  Hand-writting character ' ] ' //
    case '^': DrawDigit(axis, xyz, Caret, 12, offset, hwclock); break; //  Hand-writting character ' ^ ' //
    case '_': DrawDigit(axis, xyz, Understrike, 6, offset, hwclock); break; //  Hand-writting character ' _ ' //
    case '`': DrawDigit(axis, xyz, Grave, 6, offset, hwclock); break; //  Hand-writting character ' ` ' //
    case 'a': DrawDigit(axis, xyz, Lowercase_a , 20, offset, hwclock); break; //  Hand-writting character ' a ' //
    case 'b': DrawDigit(axis, xyz, Lowercase_b , 26, offset, hwclock); break; //  Hand-writting character ' b ' //
    case 'c': DrawDigit(axis, xyz, Lowercase_c , 18, offset, hwclock); break; //  Hand-writting character ' c ' //
    case 'd': DrawDigit(axis, xyz, Lowercase_d , 25, offset, hwclock); break; //  Hand-writting character ' d ' //
    case 'e': DrawDigit(axis, xyz, Lowercase_e , 20, offset, hwclock); break; //  Hand-writting character ' e ' //
    case 'f': DrawDigit(axis, xyz, Lowercase_f , 21, offset, hwclock); break; //  Hand-writting character ' f ' //
    case 'g': DrawDigit(axis, xyz, Lowercase_g , 24, offset, hwclock); break; //  Hand-writting character ' g ' //
    case 'h': DrawDigit(axis, xyz, Lowercase_h , 26, offset, hwclock); break; //  Hand-writting character ' h ' //
    case 'i': DrawDigit(axis, xyz, Lowercase_i , 15, offset, hwclock); break; //  Hand-writting character ' i ' //
    case 'j': DrawDigit(axis, xyz, Lowercase_j , 17, offset, hwclock); break; //  Hand-writting character ' j ' //
    case 'k': DrawDigit(axis, xyz, Lowercase_k , 25, offset, hwclock); break; //  Hand-writting character ' k ' //
    case 'l': DrawDigit(axis, xyz, Lowercase_l , 17, offset, hwclock); break; //  Hand-writting character ' l ' //
    case 'm': DrawDigit(axis, xyz, Lowercase_m , 25, offset, hwclock); break; //  Hand-writting character ' m ' //
    case 'n': DrawDigit(axis, xyz, Lowercase_n , 21, offset, hwclock); break; //  Hand-writting character ' n ' //
    case 'o': DrawDigit(axis, xyz, Lowercase_o , 20, offset, hwclock); break; //  Hand-writting character ' o ' //
    case 'p': DrawDigit(axis, xyz, Lowercase_p , 24, offset, hwclock); break; //  Hand-writting character ' p ' //
    case 'q': DrawDigit(axis, xyz, Lowercase_q , 22, offset, hwclock); break; //  Hand-writting character ' q ' //
    case 'r': DrawDigit(axis, xyz, Lowercase_r , 18, offset, hwclock); break; //  Hand-writting character ' r ' //
    case 's': DrawDigit(axis, xyz, Lowercase_s , 18, offset, hwclock); break; //  Hand-writting character ' s ' //
    case 't': DrawDigit(axis, xyz, Lowercase_t , 17, offset, hwclock); break; //  Hand-writting character ' t ' //
    case 'u': DrawDigit(axis, xyz, Lowercase_u , 21, offset, hwclock); break; //  Hand-writting character ' u ' //
    case 'v': DrawDigit(axis, xyz, Lowercase_v , 18, offset, hwclock); break; //  Hand-writting character ' v ' //
    case 'w': DrawDigit(axis, xyz, Lowercase_w , 24, offset, hwclock); break; //  Hand-writting character ' w ' //
    case 'x': DrawDigit(axis, xyz, Lowercase_x , 19, offset, hwclock); break; //  Hand-writting character ' x ' //
    case 'y': DrawDigit(axis, xyz, Lowercase_y , 23, offset, hwclock); break; //  Hand-writting character ' y ' //
    case 'z': DrawDigit(axis, xyz, Lowercase_z , 20, offset, hwclock); break; //  Hand-writting character ' z ' //
    case '{': DrawDigit(axis, xyz, Braces1, 17, offset, hwclock); break; //  Hand-writting character ' { ' //
    case '|': DrawDigit(axis, xyz, Vbar, 12, offset, hwclock); break; //  Hand-writting character ' | ' //
    case '}': DrawDigit(axis, xyz, Braces2, 17, offset, hwclock); break; //  Hand-writting character ' } ' //
    case '~': DrawDigit(axis, xyz, Tilde, 10, offset, hwclock); break; //  Hand-writting character ' ~ ' //
  }
}


void myCUBE::DrawDigit(char axis, byte xyz, byte dots[][2], byte siz, byte offset, bool hwclock)
{
    switch (axis)
        {
          case AXIS_X:
            for (int i = 0; i < siz; i++)
              {
                if (hwclock)
                setvoxel(xyz, offset + dots[i][0], 6-(dots[i][1]));
                else
                setvoxel(xyz, offset + dots[i][0], 7-(dots[i][1]));
                delay(20);
              }
              break;
        
          case AXIS_Y:
            for (int i = 0; i < siz; i++)
              {
                setvoxel(7 - dots[i][0], xyz, 7-(dots[i][1]));                
                delay(20);
              }
            break;
          case AXIS_Z:
            for (int i = 0; i < siz; i++)
              {
                setvoxel(7 - dots[i][1], offset + dots[i][0], xyz);             
                delay(20);
              }
              break;          
      }
}

void myCUBE::Eraser(char axis, byte xyz, uint8_t offset)
{
  for (int i = 0; i < 33; i++)
  {
    byte z1 = Delete[i][0];
    byte x1 = Delete[i][1];
    byte z2 = z1 + 1;
    byte x2 = x1 + 1;
    z1 = checkConstrains(z1, 0, 7);
    z2 = checkConstrains(z2, 0, 7);
    x1 = checkConstrains(x1, 0, 7);
    x2 = checkConstrains(x2, 0, 7);
    fillRectangle(axis, xyz, z1, x1, z2, x2, 1, offset);
    delay(20);
    fillRectangle(axis, xyz, z1, x1, z2, x2, 0, offset);
  }
}


void myCUBE::fillRectangle(char axis, uint8_t xyz, uint8_t z1, uint8_t x1, uint8_t z2, uint8_t x2, bool state, uint8_t offset)
{
   
    switch (axis)
      {
        case AXIS_Y:
          for (uint8_t z = z1; z <= z2; z++) 
          {
            for (uint8_t x = x1; x <= x2; x++) 
            {
              if (state)
              setvoxel(x, xyz, z);
              else
              clrvoxel(x, xyz, z);      
            }
          }
          break;
        case AXIS_X:
          for (uint8_t z = z1; z <= z2; z++) 
          {
            for (uint8_t x = x1; x <= x2; x++) 
            {
              if (state)
              setvoxel(xyz, offset + x, z);  
              else
              clrvoxel(xyz, offset + x, z);     
            }
          }
          break;
        case AXIS_Z:
          for (uint8_t z = z1; z <= z2; z++) 
          {
            for (uint8_t x = x1; x <= x2; x++) 
            {
              if (state)
              setvoxel(x, offset + z, xyz);
              else
              clrvoxel(x, offset + z, xyz);      
            }
          }
          break;          
      }
}

int myCUBE::checkConstrains(int value, int min, int max) {
  if(value < min) {
    return min;
  } else if (value > max) {
    return max;
  } else {
    return value;
  }
}

void myCUBE::TransitionShift(char axis, const type_polarity polarity, const uint8_t delayms)
{
  uint8_t x;

  for (x = 0; x < 8; x++)
  {
    shift(axis, ((polarity == POSITIVE) << 1) - 1);
    delay_ms(delayms);
  }
}


void myCUBE::TransitionScroll(char axis, const type_polarity polarity, const uint8_t delayx)
{
  uint8_t x;

  for (x = 0; x < 7; x++)
  {
    TranslateScroll(axis, ((polarity == POSITIVE) << 1) - 1);
    delay_ms(delayx);
  }
}
 

void myCUBE::DIY_shiftOut(uint8_t DATA)
{
    uint8_t i;
    uint8_t val;
    for (i = 0; i<8; i++)  
    {
      val = !!(DATA & (1 << (i)));
      if (val) *outDATA &= ~bitDATA;
          else *outDATA |= bitDATA;      
	                        
      //Clock Pulse
      *outCLOCK &= ~bitCLOCK;
      *outCLOCK |= bitCLOCK;               		
    }
}

void myCUBE::RowScan(byte row)
{
  if (row & 0x01) *outRowA |= bitRowA;
    else *outRowA &= ~bitRowA;
  
  if (row & 0x02) *outRowB |= bitRowB;
    else *outRowB &= ~bitRowB;

  if (row & 0x04) *outRowC |= bitRowC;
    else *outRowC &= ~bitRowC;

  if (row & 0x08) *outRowD |= bitRowD;
    else *outRowD &= ~bitRowD;
}  

void myCUBE::Show()
{
    *outOE |= bitOE;
    
    DIY_shiftOut(~(cube[row][0])); 
    DIY_shiftOut(~(cube[row][1]));
    DIY_shiftOut(~(cube[row][2])); 
    DIY_shiftOut(~(cube[row][3]));
    DIY_shiftOut(~(cube[row][4]));
    DIY_shiftOut(~(cube[row][5])); 
    DIY_shiftOut(~(cube[row][6]));
    DIY_shiftOut(~(cube[row][7]));
    
    RowScan(row);
    *outSTB &= ~bitSTB; 
    *outSTB |= bitSTB;       
    *outOE &= ~bitOE; 
    row++;
    if (row==16) row=0;
}
//// Timer setup

void myCUBE::Timer1Setup()
{
//We use Timer 1 to refresh the cube
TCCR1A = B00000000;//Register A all 0's since we're not toggling any pins
TCCR1B = B00001011;//bit 3 set to place in CTC mode, will call an interrupt on a counter match
//bits 0 and 1 are set to divide the clock by 64, so 16MHz/64=250kHz
TIMSK1 = B00000010;//bit 1 set to call the interrupt on an OCR1A match
OCR1A=124; // you can play with this, but I set it to 124, which means:
//our clock runs at 250kHz, which is 1/250kHz = 4us
//with OCR1A set to 124, this means the interrupt will be called every (124+1)x4us=500us, 
// which gives a multiplex frequency of about 2kHz
 
}


