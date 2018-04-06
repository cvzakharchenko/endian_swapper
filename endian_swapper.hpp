/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <cstdint>

namespace EndianSwapper
{
    namespace utilitary__
    {

        class SwapByteBase
        {
        public:
            static bool ShouldSwap()
            {
                static const std::uint16_t swapTest = 1;
                return (*((char*)&swapTest) == 1);
            }

            static void SwapBytes(std::uint8_t& v1, std::uint8_t& v2)
            {
                std::uint8_t tmp = v1;
                v1 = v2;
                v2 = tmp;
            }
        };

        template <class T, int S>
        class SwapByte : public SwapByteBase
        {
        };

        template <class T>
        class SwapByte<T, 1> : public SwapByteBase
        {
        public:
            static T Swap(T v)
            {
                return v;
            }
        };

        template <class T>
        class SwapByte<T, 2> : public SwapByteBase
        {
        public:
            static T Swap(T v)
            {
                if (ShouldSwap())
                    return (v >> 8) | (v << 8);
                return v;
            }
        };

        template <class T>
        class SwapByte<T, 4> : public SwapByteBase
        {
        public:
            static T Swap(T v)
            {
                if (ShouldSwap())
                {
                    return (SwapByte<std::uint16_t, 2>::Swap((std::uint32_t)v & 0xffff) << 16) | (SwapByte<std::uint16_t, 2>::Swap(((std::uint32_t)v & 0xffff0000) >> 16));
                }
                return v;
            }
        };

        template <class T>
        class SwapByte<T, 8> : public SwapByteBase
        {
        public:
            static T Swap(T v)
            {
                if (ShouldSwap())
                    return (((std::uint64_t)SwapByte<T, 4>::Swap((std::uint32_t)(v & 0xffffffffull))) << 32) | (SwapByte<T, 4>::Swap((std::uint32_t)(v >> 32)));
                return v;
            }
        };

        template <>
        class SwapByte<float, 4> : public SwapByteBase
        {
        public:
            static float Swap(float v)
            {
                union { float f; std::uint8_t c[4]; };
                f = v;
                if (ShouldSwap())
                {
                    SwapBytes(c[0], c[3]);
                    SwapBytes(c[1], c[2]);
                }
                return f;
            }
        };

        template <>
        class SwapByte<double, 8> : public SwapByteBase
        {
        public:
            static double Swap(double v)
            {
                union { double f; std::uint8_t c[8]; };
                f = v;
                if (ShouldSwap())
                {
                    SwapBytes(c[0], c[7]);
                    SwapBytes(c[1], c[6]);
                    SwapBytes(c[2], c[5]);
                    SwapBytes(c[3], c[4]);
                }
                return f;
            }
        };

    }; // namespace utilitary__


    template <class T>
    T swap(const T& v)
    {
        return utilitary__::SwapByte<T, sizeof(T)>::Swap(v);
    }


}; // namespace EndianSwapper
