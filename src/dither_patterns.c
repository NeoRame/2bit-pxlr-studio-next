#pragma bank 255

#include <gbdk/platform.h>
#include <string.h>

#include "gbcamera.h"

#define NUM_ONOFF_SETS 2
#define NUM_LIGHT_SETS 2
#define NUM_CONTRAST_SETS 16
#define NUM_CONTRAST_SIZE 48

static const uint8_t ditherPatterns[NUM_ONOFF_SETS][NUM_LIGHT_SETS][NUM_CONTRAST_SETS][NUM_CONTRAST_SIZE] = {
    {
        // Dither On / High Light
        {
            { 0x80, 0x8F, 0xD0, 0x8B, 0xBF, 0xE0, 0x82, 0x9B, 0xD4, 0x8E, 0xCB, 0xE4, 0x87, 0xAF, 0xDB, 0x83, 0x9F, 0xD5, 0x8A, 0xBB, 0xDF, 0x86, 0xAB, 0xD9, 0x81, 0x97, 0xD2, 0x8D, 0xC7, 0xE3, 0x80, 0x93, 0xD1, 0x8C, 0xC3, 0xE1, 0x89, 0xB7, 0xDD, 0x85, 0xA7, 0xD8, 0x88, 0xB3, 0xDC, 0x84, 0xA3, 0xD6, },
            { 0x82, 0x90, 0xC8, 0x8C, 0xBA, 0xDC, 0x84, 0x9A, 0xCD, 0x8F, 0xC4, 0xE1, 0x89, 0xAC, 0xD5, 0x85, 0x9E, 0xCE, 0x8B, 0xB6, 0xDA, 0x88, 0xA8, 0xD3, 0x83, 0x97, 0xCB, 0x8E, 0xC1, 0xDF, 0x82, 0x93, 0xC9, 0x8D, 0xBD, 0xDD, 0x8A, 0xB3, 0xD8, 0x87, 0xA5, 0xD2, 0x89, 0xAF, 0xD7, 0x86, 0xA1, 0xD0, },
            { 0x84, 0x90, 0xC0, 0x8D, 0xB4, 0xD8, 0x86, 0x99, 0xC6, 0x8F, 0xBD, 0xDE, 0x8A, 0xA8, 0xD0, 0x87, 0x9C, 0xC8, 0x8C, 0xB1, 0xD6, 0x89, 0xA5, 0xCE, 0x85, 0x96, 0xC4, 0x8E, 0xBA, 0xDC, 0x84, 0x93, 0xC2, 0x8D, 0xB7, 0xDA, 0x8B, 0xAE, 0xD4, 0x88, 0xA2, 0xCC, 0x8A, 0xAB, 0xD2, 0x87, 0x9F, 0xCA, },
            { 0x85, 0x91, 0xB8, 0x8E, 0xAE, 0xD3, 0x87, 0x98, 0xBE, 0x90, 0xB5, 0xDA, 0x8B, 0xA4, 0xCA, 0x88, 0x9A, 0xC1, 0x8D, 0xAB, 0xD1, 0x8A, 0xA2, 0xC8, 0x86, 0x95, 0xBC, 0x8F, 0xB3, 0xD8, 0x85, 0x93, 0xBA, 0x8E, 0xB0, 0xD6, 0x8C, 0xA9, 0xCF, 0x89, 0x9F, 0xC5, 0x8B, 0xA6, 0xCC, 0x88, 0x9D, 0xC3, },
            { 0x86, 0x91, 0xB1, 0x8E, 0xA9, 0xD0, 0x88, 0x97, 0xB8, 0x90, 0xAF, 0xD8, 0x8B, 0xA1, 0xC6, 0x88, 0x99, 0xBB, 0x8D, 0xA7, 0xCD, 0x8A, 0x9F, 0xC3, 0x87, 0x95, 0xB6, 0x8F, 0xAD, 0xD5, 0x86, 0x93, 0xB3, 0x8E, 0xAB, 0xD3, 0x8C, 0xA5, 0xCB, 0x8A, 0x9D, 0xC0, 0x8C, 0xA3, 0xC8, 0x89, 0x9B, 0xBE, },
            { 0x87, 0x92, 0xAA, 0x8F, 0xA4, 0xCC, 0x89, 0x96, 0xB2, 0x91, 0xA8, 0xD5, 0x8C, 0x9E, 0xC1, 0x89, 0x98, 0xB5, 0x8E, 0xA2, 0xC9, 0x8B, 0x9C, 0xBE, 0x88, 0x95, 0xAF, 0x90, 0xA7, 0xD2, 0x87, 0x93, 0xAC, 0x8F, 0xA5, 0xCF, 0x8D, 0xA1, 0xC6, 0x8B, 0x9B, 0xBB, 0x8D, 0x9F, 0xC3, 0x8A, 0x99, 0xB8, },
            { 0x88, 0x92, 0xA5, 0x8F, 0xA0, 0xC9, 0x89, 0x95, 0xAE, 0x91, 0xA3, 0xD2, 0x8D, 0x9B, 0xBD, 0x8A, 0x96, 0xB1, 0x8E, 0x9F, 0xC6, 0x8C, 0x9A, 0xBA, 0x89, 0x94, 0xAB, 0x90, 0xA2, 0xCF, 0x88, 0x93, 0xA8, 0x90, 0xA1, 0xCC, 0x8E, 0x9D, 0xC3, 0x8B, 0x99, 0xB7, 0x8D, 0x9C, 0xC0, 0x8B, 0x97, 0xB4, },
            { 0x89, 0x92, 0xA2, 0x8F, 0x9E, 0xC6, 0x8A, 0x95, 0xAB, 0x91, 0xA1, 0xCF, 0x8D, 0x9A, 0xBA, 0x8B, 0x96, 0xAE, 0x8F, 0x9D, 0xC3, 0x8C, 0x99, 0xB7, 0x8A, 0x94, 0xA8, 0x90, 0xA0, 0xCC, 0x89, 0x93, 0xA5, 0x90, 0x9F, 0xC9, 0x8E, 0x9C, 0xC0, 0x8C, 0x98, 0xB4, 0x8E, 0x9B, 0xBD, 0x8B, 0x97, 0xB1, },
            { 0x8A, 0x92, 0xA1, 0x90, 0x9D, 0xBE, 0x8B, 0x94, 0xA8, 0x91, 0xA0, 0xC5, 0x8E, 0x99, 0xB4, 0x8C, 0x95, 0xAA, 0x8F, 0x9C, 0xBB, 0x8D, 0x98, 0xB2, 0x8B, 0x93, 0xA5, 0x91, 0x9F, 0xC3, 0x8A, 0x92, 0xA3, 0x90, 0x9E, 0xC0, 0x8F, 0x9B, 0xB9, 0x8D, 0x97, 0xAF, 0x8E, 0x9A, 0xB6, 0x8C, 0x96, 0xAD, },
            { 0x8B, 0x92, 0xA0, 0x90, 0x9C, 0xB6, 0x8C, 0x94, 0xA5, 0x91, 0x9F, 0xBC, 0x8E, 0x99, 0xAF, 0x8C, 0x95, 0xA7, 0x8F, 0x9B, 0xB4, 0x8E, 0x98, 0xAD, 0x8B, 0x93, 0xA3, 0x91, 0x9E, 0xBA, 0x8B, 0x92, 0xA1, 0x90, 0x9D, 0xB8, 0x8F, 0x9A, 0xB2, 0x8D, 0x97, 0xAB, 0x8E, 0x99, 0xB0, 0x8D, 0x96, 0xA9, },
            { 0x8C, 0x92, 0x9E, 0x90, 0x9B, 0xAE, 0x8D, 0x94, 0xA2, 0x91, 0x9D, 0xB2, 0x8F, 0x98, 0xA9, 0x8D, 0x95, 0xA3, 0x90, 0x9A, 0xAD, 0x8E, 0x97, 0xA7, 0x8C, 0x93, 0xA0, 0x91, 0x9C, 0xB1, 0x8C, 0x92, 0x9F, 0x90, 0x9B, 0xAF, 0x8F, 0x99, 0xAB, 0x8E, 0x96, 0xA6, 0x8F, 0x98, 0xAA, 0x8D, 0x95, 0xA4, },
            { 0x8D, 0x92, 0x9C, 0x90, 0x99, 0xA8, 0x8D, 0x93, 0x9F, 0x91, 0x9B, 0xAB, 0x8F, 0x97, 0xA4, 0x8E, 0x94, 0xA0, 0x90, 0x98, 0xA7, 0x8F, 0x96, 0xA3, 0x8D, 0x93, 0x9E, 0x91, 0x9A, 0xAA, 0x8D, 0x92, 0x9D, 0x91, 0x9A, 0xA9, 0x90, 0x98, 0xA6, 0x8E, 0x95, 0xA2, 0x8F, 0x97, 0xA5, 0x8E, 0x95, 0xA1, },
            { 0x8E, 0x92, 0x9B, 0x91, 0x98, 0xA2, 0x8E, 0x93, 0x9C, 0x91, 0x9A, 0xA4, 0x90, 0x96, 0xA0, 0x8F, 0x94, 0x9D, 0x90, 0x98, 0xA1, 0x8F, 0x95, 0x9F, 0x8E, 0x93, 0x9C, 0x91, 0x99, 0xA3, 0x8E, 0x92, 0x9B, 0x91, 0x99, 0xA3, 0x90, 0x97, 0xA1, 0x8F, 0x95, 0x9E, 0x90, 0x97, 0xA0, 0x8F, 0x94, 0x9E, },
            { 0x8F, 0x92, 0x99, 0x91, 0x97, 0x9E, 0x8F, 0x93, 0x9A, 0x91, 0x98, 0x9F, 0x90, 0x95, 0x9C, 0x8F, 0x93, 0x9A, 0x91, 0x96, 0x9D, 0x90, 0x95, 0x9C, 0x8F, 0x92, 0x99, 0x91, 0x98, 0x9F, 0x8F, 0x92, 0x99, 0x91, 0x97, 0x9E, 0x90, 0x96, 0x9D, 0x90, 0x94, 0x9B, 0x90, 0x95, 0x9C, 0x8F, 0x94, 0x9B, },
            { 0x90, 0x92, 0x97, 0x91, 0x95, 0x99, 0x90, 0x92, 0x97, 0x91, 0x96, 0x99, 0x91, 0x94, 0x98, 0x90, 0x93, 0x97, 0x91, 0x95, 0x99, 0x90, 0x94, 0x98, 0x90, 0x92, 0x97, 0x91, 0x96, 0x99, 0x90, 0x92, 0x97, 0x91, 0x96, 0x99, 0x91, 0x95, 0x98, 0x90, 0x93, 0x98, 0x91, 0x94, 0x98, 0x90, 0x93, 0x97, },
            { 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, },
        },
        // Dither On / Low Light
        {
            { 0x80, 0x94, 0xDC, 0x8F, 0xCA, 0xF6, 0x83, 0xA1, 0xE2, 0x92, 0xD7, 0xFC, 0x8A, 0xB8, 0xED, 0x85, 0xA6, 0xE4, 0x8D, 0xC5, 0xF4, 0x88, 0xB3, 0xEB, 0x82, 0x9D, 0xE0, 0x91, 0xD3, 0xFA, 0x81, 0x98, 0xDE, 0x90, 0xCE, 0xF8, 0x8C, 0xC1, 0xF1, 0x87, 0xAF, 0xE9, 0x8B, 0xBC, 0xEF, 0x86, 0xAA, 0xE6, },
            { 0x82, 0x95, 0xD2, 0x90, 0xC2, 0xF3, 0x85, 0xA0, 0xDA, 0x93, 0xCE, 0xFC, 0x8B, 0xB3, 0xE8, 0x86, 0xA4, 0xDD, 0x8F, 0xBE, 0xF0, 0x8A, 0xAF, 0xE5, 0x84, 0x9C, 0xD7, 0x92, 0xCA, 0xF9, 0x83, 0x98, 0xD4, 0x91, 0xC6, 0xF6, 0x8D, 0xBB, 0xEE, 0x89, 0xAB, 0xE2, 0x8C, 0xB7, 0xEB, 0x87, 0xA8, 0xE0, },
            { 0x84, 0x96, 0xCA, 0x91, 0xBD, 0xF1, 0x87, 0x9F, 0xD3, 0x94, 0xC6, 0xFB, 0x8D, 0xB0, 0xE4, 0x88, 0xA3, 0xD7, 0x90, 0xB9, 0xEE, 0x8B, 0xAC, 0xE1, 0x86, 0x9C, 0xD0, 0x93, 0xC3, 0xF8, 0x85, 0x99, 0xCD, 0x92, 0xC0, 0xF5, 0x8F, 0xB6, 0xEB, 0x8A, 0xA9, 0xDD, 0x8E, 0xB3, 0xE7, 0x89, 0xA6, 0xDA, },
            { 0x86, 0x96, 0xC4, 0x92, 0xB8, 0xF0, 0x89, 0x9E, 0xCF, 0x95, 0xC1, 0xFB, 0x8E, 0xAD, 0xE1, 0x8A, 0xA1, 0xD2, 0x91, 0xB5, 0xEC, 0x8D, 0xAA, 0xDD, 0x88, 0x9B, 0xCB, 0x94, 0xBE, 0xF7, 0x87, 0x98, 0xC7, 0x93, 0xBB, 0xF3, 0x90, 0xB2, 0xE8, 0x8C, 0xA7, 0xDA, 0x8F, 0xAF, 0xE5, 0x8B, 0xA4, 0xD6, },
            { 0x88, 0x97, 0xBE, 0x93, 0xB4, 0xEE, 0x8A, 0x9E, 0xCA, 0x96, 0xBB, 0xFA, 0x8F, 0xAA, 0xDE, 0x8B, 0xA0, 0xCE, 0x92, 0xB1, 0xEA, 0x8E, 0xA8, 0xDA, 0x89, 0x9B, 0xC6, 0x95, 0xB9, 0xF6, 0x88, 0x99, 0xC2, 0x94, 0xB6, 0xF2, 0x91, 0xAF, 0xE6, 0x8D, 0xA5, 0xD6, 0x90, 0xAC, 0xE2, 0x8C, 0xA3, 0xD2, },
            { 0x8A, 0x97, 0xB8, 0x93, 0xAF, 0xED, 0x8C, 0x9D, 0xC5, 0x96, 0xB5, 0xFA, 0x90, 0xA7, 0xDB, 0x8D, 0x9F, 0xC9, 0x92, 0xAD, 0xE8, 0x8F, 0xA5, 0xD7, 0x8B, 0x9B, 0xC0, 0x95, 0xB3, 0xF6, 0x8A, 0x99, 0xBC, 0x94, 0xB1, 0xF1, 0x92, 0xAB, 0xE4, 0x8E, 0xA3, 0xD2, 0x91, 0xA9, 0xDF, 0x8E, 0xA1, 0xCE, },
            { 0x8B, 0x98, 0xB2, 0x94, 0xAB, 0xE4, 0x8D, 0x9C, 0xBE, 0x97, 0xB0, 0xF0, 0x91, 0xA5, 0xD3, 0x8E, 0x9E, 0xC2, 0x93, 0xA9, 0xE0, 0x90, 0xA3, 0xCF, 0x8C, 0x9B, 0xBA, 0x96, 0xAE, 0xEC, 0x8B, 0x99, 0xB6, 0x95, 0xAD, 0xE8, 0x93, 0xA8, 0xDB, 0x8F, 0xA1, 0xCB, 0x92, 0xA6, 0xD7, 0x8F, 0xA0, 0xC6, },
            { 0x8C, 0x98, 0xAC, 0x95, 0xA7, 0xDB, 0x8E, 0x9B, 0xB7, 0x97, 0xAA, 0xE7, 0x92, 0xA2, 0xCB, 0x8F, 0x9D, 0xBB, 0x94, 0xA5, 0xD7, 0x91, 0xA0, 0xC7, 0x8D, 0x9A, 0xB3, 0x96, 0xA9, 0xE3, 0x8C, 0x99, 0xAF, 0x95, 0xA8, 0xDF, 0x93, 0xA4, 0xD3, 0x90, 0x9F, 0xC3, 0x92, 0xA3, 0xCF, 0x8F, 0x9E, 0xBF, },
            { 0x8D, 0x98, 0xAA, 0x95, 0xA5, 0xD0, 0x8F, 0x9B, 0xB3, 0x97, 0xA8, 0xD9, 0x92, 0xA1, 0xC3, 0x8F, 0x9C, 0xB6, 0x94, 0xA4, 0xCD, 0x91, 0x9F, 0xC0, 0x8E, 0x9A, 0xB0, 0x96, 0xA7, 0xD6, 0x8D, 0x99, 0xAD, 0x95, 0xA6, 0xD3, 0x93, 0xA3, 0xC9, 0x91, 0x9E, 0xBD, 0x93, 0xA2, 0xC6, 0x90, 0x9D, 0xB9, },
            { 0x8E, 0x98, 0xA8, 0x95, 0xA4, 0xC6, 0x8F, 0x9B, 0xAF, 0x97, 0xA7, 0xCD, 0x93, 0xA0, 0xBC, 0x90, 0x9C, 0xB2, 0x94, 0xA3, 0xC3, 0x92, 0x9F, 0xB9, 0x8F, 0x9A, 0xAD, 0x96, 0xA6, 0xCB, 0x8E, 0x99, 0xAA, 0x96, 0xA5, 0xC8, 0x94, 0xA2, 0xC1, 0x91, 0x9E, 0xB7, 0x93, 0xA1, 0xBE, 0x91, 0x9D, 0xB4, },
            { 0x8F, 0x98, 0xA6, 0x95, 0xA2, 0xBC, 0x90, 0x9A, 0xAB, 0x97, 0xA5, 0xC2, 0x93, 0x9F, 0xB5, 0x91, 0x9B, 0xAD, 0x95, 0xA1, 0xBA, 0x92, 0x9E, 0xB3, 0x90, 0x99, 0xA9, 0x96, 0xA4, 0xC0, 0x8F, 0x98, 0xA7, 0x96, 0xA3, 0xBE, 0x94, 0xA0, 0xB8, 0x92, 0x9D, 0xB1, 0x94, 0x9F, 0xB6, 0x91, 0x9C, 0xAF, },
            { 0x90, 0x98, 0xA4, 0x96, 0xA1, 0xB4, 0x91, 0x9A, 0xA8, 0x97, 0xA3, 0xB8, 0x94, 0x9E, 0xAF, 0x92, 0x9B, 0xA9, 0x95, 0xA0, 0xB3, 0x93, 0x9D, 0xAD, 0x91, 0x99, 0xA6, 0x97, 0xA2, 0xB7, 0x90, 0x98, 0xA5, 0x96, 0xA1, 0xB5, 0x95, 0x9F, 0xB1, 0x93, 0x9C, 0xAC, 0x94, 0x9E, 0xB0, 0x92, 0x9B, 0xAA, },
            { 0x92, 0x98, 0xA1, 0x96, 0x9E, 0xAD, 0x93, 0x99, 0xA4, 0x97, 0xA0, 0xB0, 0x95, 0x9C, 0xA9, 0x93, 0x9A, 0xA5, 0x96, 0x9E, 0xAC, 0x94, 0x9B, 0xA8, 0x92, 0x99, 0xA3, 0x97, 0x9F, 0xAF, 0x92, 0x98, 0xA2, 0x96, 0x9F, 0xAE, 0x95, 0x9D, 0xAB, 0x94, 0x9B, 0xA7, 0x95, 0x9D, 0xAA, 0x93, 0x9A, 0xA6, },
            { 0x94, 0x98, 0x9D, 0x97, 0x9B, 0xA5, 0x94, 0x98, 0x9F, 0x97, 0x9C, 0xA7, 0x96, 0x9A, 0xA2, 0x95, 0x99, 0x9F, 0x96, 0x9B, 0xA4, 0x95, 0x9A, 0xA1, 0x94, 0x98, 0x9E, 0x97, 0x9C, 0xA6, 0x94, 0x98, 0x9D, 0x97, 0x9C, 0xA5, 0x96, 0x9B, 0xA3, 0x95, 0x99, 0xA1, 0x96, 0x9A, 0xA3, 0x95, 0x99, 0xA0, },
            { 0x96, 0x98, 0x99, 0x97, 0x98, 0x9E, 0x96, 0x98, 0x9A, 0x97, 0x98, 0x9F, 0x97, 0x98, 0x9C, 0x96, 0x98, 0x9A, 0x97, 0x98, 0x9D, 0x96, 0x98, 0x9C, 0x96, 0x98, 0x99, 0x97, 0x98, 0x9F, 0x96, 0x98, 0x99, 0x97, 0x98, 0x9E, 0x97, 0x98, 0x9D, 0x96, 0x98, 0x9B, 0x97, 0x98, 0x9C, 0x96, 0x98, 0x9B, },
            { 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, },
        },
    },
    {
        // No Dither / High Light
        {
            { 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, 0x80, 0x8F, 0xD0, },
            { 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, 0x82, 0x90, 0xC8, },
            { 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, 0x84, 0x90, 0xC0, },
            { 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, 0x85, 0x91, 0xB8, },
            { 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, 0x86, 0x91, 0xB1, },
            { 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, 0x87, 0x92, 0xAA, },
            { 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, 0x88, 0x92, 0xA5, },
            { 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, 0x89, 0x92, 0xA2, },
            { 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, 0x8A, 0x92, 0xA1, },
            { 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, 0x8B, 0x92, 0xA0, },
            { 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, 0x8C, 0x92, 0x9E, },
            { 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, 0x8D, 0x92, 0x9C, },
            { 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, 0x8E, 0x92, 0x9B, },
            { 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, 0x8F, 0x92, 0x99, },
            { 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, 0x90, 0x92, 0x97, },
            { 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, },
        },
        // No Dither / Low Light
        {
            { 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, 0x80, 0x94, 0xDC, },
            { 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, 0x82, 0x95, 0xD2, },
            { 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, 0x84, 0x96, 0xCA, },
            { 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, 0x86, 0x96, 0xC4, },
            { 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, 0x88, 0x97, 0xBE, },
            { 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, 0x8A, 0x97, 0xB8, },
            { 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, 0x8B, 0x98, 0xB2, },
            { 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, 0x8C, 0x98, 0xAC, },
            { 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, 0x8D, 0x98, 0xAA, },
            { 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, 0x8E, 0x98, 0xA8, },
            { 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, 0x8F, 0x98, 0xA6, },
            { 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, 0x90, 0x98, 0xA4, },
            { 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, 0x92, 0x98, 0xA1, },
            { 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, 0x94, 0x98, 0x9D, },
            { 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, 0x96, 0x98, 0x99, },
            { 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, },
        },
    },
};

void dither_pattern_apply(uint8_t dithering, uint8_t ditheringHighLight, uint8_t current_contrast) BANKED {
    memcpy(CAM_DITHERPATTERN, &ditherPatterns[(dithering) ? 0 : 1][(ditheringHighLight) ? 0 : 1][current_contrast], sizeof(CAM_DITHERPATTERN));
}
