/*
 * framesIndexers.h
 *
 *  Created on: 23 sept. 2020
 *      Author: deros
 */

#ifndef INC_FRAMESINDEXERS_H_
#define INC_FRAMESINDEXERS_H_

#include "stdbool.h"

static const uint16_t f0[] = {	 19,   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,   32,   33,   34,	// 1
								 37,   38,   39,   40,   41,   42,   43,   44,   45,   46,   47,   48,   49,   50,   51,   52,	// 2
								 55,   56,   57,   58,   59,   60,   61,   62,   63,   64,   65,   66,   67,   68,   69,   70,  // 3
								 73,   74,   75,   76,   77,   78,   79,   80,   81,   82,   83,   84,   85,   86,   87,   88,  // 4
								 91,   92,   93,   94,   95,   96,   97,   98,   99,  100,  101,  102,  103,  104,  105,  106,  // 5
								109,  110,  111,  112,  113,  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,  124,	// 6
								127,  128,  129,  130,  131,  132,  133,  134,  135,  136,  137,  138,  139,  140,  141,  142,	// 7
								145,  146,  147,  148,  149,  150,  151,  152,  153,  154,  155,  156,  157,  158,  159,  160,	// 8
								163,  164,  165,  166,  167,  168,  169,  170,  171,  172,  173,  174,  175,  176,  177,  178,	// 9
								181,  182,  183,  184,  185,  186,  187,  188,  189,  190,  191,  192,  193,  194,  195,  196,	// 10
								199,  200,  201,  202,  203,  204,  205,  206,  207,  208,  209,  210,  211,  212,  213,  214,	// 11
								217,  218,  219,  220,  221,  222,  223,  224,  225,  226,  227,  228,  229,  230,  231,  232,	// 12
								235,  236,  237,  238,  239,  240,  241,  242,  243,  244,  245,  246,  247,  248,  249,  250,	// 13
								253,  254,  255,  256,  257,  258,  259,  260,  261,  262,  263,  264,  265,  266,  267,  268,	// 14
								271,  272,  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,  285,  286,	// 15
								289,  290,  291,  292,  293,  294,  295,  296,  297,  298,  299,  300,  301,  302,  303,  304 	// 16
							};

static const uint16_t f1 [] = {	 37,   38,   39,   40,   41,   42,   43,   44,   45,   46,   47,   48,   49,   50,   51,   52,	// 1
								 55,   56,   57,   58,   59,   60,   61,   62,   63,   64,   65,   66,   67,   68,   69,   70,	// 2
								 73,   74,   75,   76,   77,   78,   79,   80,   81,   82,   83,   84,   85,   86,   87,   88,  // 3
								 91,   92,   93,   94,   95,   96,   97,   98,   99,  100,  101,  102,  103,  104,  105,  106,  // 4
								109,  110,  111,  112,  113,  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,  124,  // 5
								127,  128,  129,  130,  131,  132,  133,  134,  135,  136,  137,  138,  139,  140,  141,  142,	// 6
								145,  146,  147,  148,  149,  150,  151,  152,  153,  154,  155,  156,  157,  158,  159,  160,	// 7
								163,  164,  165,  166,  167,  168,  169,  170,  171,  172,  173,  174,  175,  176,  177,  178,	// 8
								181,  182,  183,  184,  185,  186,  187,  188,  189,  190,  191,  192,  193,  194,  195,  196,	// 9
								199,  200,  201,  202,  203,  204,  205,  206,  207,  208,  209,  210,  211,  212,  213,  214,	// 10
								217,  218,  219,  220,  221,  222,  223,  224,  225,  226,  227,  228,  229,  230,  231,  232,	// 11
								235,  236,  237,  238,  239,  240,  241,  242,  243,  244,  245,  246,  247,  248,  249,  250,	// 12
								253,  254,  255,  256,  257,  258,  259,  260,  261,  262,  263,  264,  265,  266,  267,  268,	// 13
								271,  272,  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,  285,  286,	// 14
								289,  290,  291,  292,  293,  294,  295,  296,  297,  298,  299,  300,  301,  302,  303,  304,	// 15
								307,  308,  309,  310,  311,  312,  313,  314,  315,  316,  317,  318,  319,  320,  321,  322 	// 16
							};

static const uint16_t f2 [] = {	  1,    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,	// 1
								 19,   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,   32,   33,   34,	// 2
								 37,   38,   39,   40,   41,   42,   43,   44,   45,   46,   47,   48,   49,   50,   51,   52,  // 3
								 55,   56,   57,   58,   59,   60,   61,   62,   63,   64,   65,   66,   67,   68,   69,   70,  // 4
								 73,   74,   75,   76,   77,   78,   79,   80,   81,   82,   83,   84,   85,   86,   87,   88,  // 5
								 91,   92,   93,   94,   95,   96,   97,   98,   99,  100,  101,  102,  103,  104,  105,  106,	// 6
								109,  110,  111,  112,  113,  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,  124,	// 7
								127,  128,  129,  130,  131,  132,  133,  134,  135,  136,  137,  138,  139,  140,  141,  142,	// 8
								145,  146,  147,  148,  149,  150,  151,  152,  153,  154,  155,  156,  157,  158,  159,  160,	// 9
								163,  164,  165,  166,  167,  168,  169,  170,  171,  172,  173,  174,  175,  176,  177,  178,	// 10
								181,  182,  183,  184,  185,  186,  187,  188,  189,  190,  191,  192,  193,  194,  195,  196,	// 11
								199,  200,  201,  202,  203,  204,  205,  206,  207,  208,  209,  210,  211,  212,  213,  214,	// 12
								217,  218,  219,  220,  221,  222,  223,  224,  225,  226,  227,  228,  229,  230,  231,  232,	// 13
								235,  236,  237,  238,  239,  240,  241,  242,  243,  244,  245,  246,  247,  248,  249,  250,	// 14
								253,  254,  255,  256,  257,  258,  259,  260,  261,  262,  263,  264,  265,  266,  267,  268,	// 15
								271,  272,  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,  285,  286 	// 16
							};

static const uint16_t f3 [] = {	 20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,   32,   33,   34,   35,	// 1
								 38,   39,   40,   41,   42,   43,   44,   45,   46,   47,   48,   49,   50,   51,   52,   53,	// 2
								 56,   57,   58,   59,   60,   61,   62,   63,   64,   65,   66,   67,   68,   69,   70,   71,  // 3
								 74,   75,   76,   77,   78,   79,   80,   81,   82,   83,   84,   85,   86,   87,   88,   89,  // 4
								 92,   93,   94,   95,   96,   97,   98,   99,  100,  101,  102,  103,  104,  105,  106,  107,  // 5
								110,  111,  112,  113,  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,  124,  125,	// 6
								128,  129,  130,  131,  132,  133,  134,  135,  136,  137,  138,  139,  140,  141,  142,  143,	// 7
								146,  147,  148,  149,  150,  151,  152,  153,  154,  155,  156,  157,  158,  159,  160,  161,	// 8
								164,  165,  166,  167,  168,  169,  170,  171,  172,  173,  174,  175,  176,  177,  178,  179,	// 9
								182,  183,  184,  185,  186,  187,  188,  189,  190,  191,  192,  193,  194,  195,  196,  197,	// 10
								200,  201,  202,  203,  204,  205,  206,  207,  208,  209,  210,  211,  212,  213,  214,  215,	// 11
								218,  219,  220,  221,  222,  223,  224,  225,  226,  227,  228,  229,  230,  231,  232,  233,	// 12
								236,  237,  238,  239,  240,  241,  242,  243,  244,  245,  246,  247,  248,  249,  250,  251,	// 13
								254,  255,  256,  257,  258,  259,  260,  261,  262,  263,  264,  265,  266,  267,  268,  269,	// 14
								272,  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,  285,  286,  287,	// 15
								290,  291,  292,  293,  294,  295,  296,  297,  298,  299,  300,  301,  302,  303,  304,  305 	// 16
							};

static const uint16_t f4 [] = {	   18,   19,   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,   32,   33,	// 1
								   36,   37,   38,   39,   40,   41,   42,   43,   44,   45,   46,   47,   48,   49,   50,   51,	// 2
								   54,   55,   56,   57,   58,   59,   60,   61,   62,   63,   64,   65,   66,   67,   68,   69,  	// 3
								   72,   73,   74,   75,   76,   77,   78,   79,   80,   81,   82,   83,   84,   85,   86,   87,  	// 4
								   90,   91,   92,   93,   94,   95,   96,   97,   98,   99,  100,  101,  102,  103,  104,  105,  	// 5
								  108,  109,  110,  111,  112,  113,  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,	// 6
								  126,  127,  128,  129,  130,  131,  132,  133,  134,  135,  136,  137,  138,  139,  140,  141,	// 7
								  144,  145,  146,  147,  148,  149,  150,  151,  152,  153,  154,  155,  156,  157,  158,  159,	// 8
								  162,  163,  164,  165,  166,  167,  168,  169,  170,  171,  172,  173,  174,  175,  176,  177,	// 9
								  180,  181,  182,  183,  184,  185,  186,  187,  188,  189,  190,  191,  192,  193,  194,  195,	// 10
								  198,  199,  200,  201,  202,  203,  204,  205,  206,  207,  208,  209,  210,  211,  212,  213,	// 11
								  216,  217,  218,  219,  220,  221,  222,  223,  224,  225,  226,  227,  228,  229,  230,  231,	// 12
								  234,  235,  236,  237,  238,  239,  240,  241,  242,  243,  244,  245,  246,  247,  248,  249,	// 13
								  252,  253,  254,  255,  256,  257,  258,  259,  260,  261,  262,  263,  264,  265,  266,  267,	// 14
								  270,  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,  285,	// 15
								  288,  289,  290,  291,  292,  293,  294,  295,  296,  297,  298,  299,  300,  301,  302,  303 	// 16
							};



static const bool fSelect[] = {		false, false,  false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,	// 1
									false, false,  false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,	// 2
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 3
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 4
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 5
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 6
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 7
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 8
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 9
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 10
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 11
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 12
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 13
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 14
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 15
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 16
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false,	// 17
									false,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  false 	// 18
								};

#endif /* INC_FRAMESINDEXERS_H_ */
