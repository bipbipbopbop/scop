#ifndef PARSING_OBJ_WAVEFRONT_DATA_HPP
#define PARSING_OBJ_WAVEFRONT_DATA_HPP

#include <array>
#include <vector>

// Basic Container definitions
template <typename T>
using Array2D = std::array<T, 2>;
template <typename T>
using Array3D = std::array<T, 3>;
template <typename T>
using Array4D = std::array<T, 4>;

// .obj data types
using Vertex = Array4D<float>;
using VTexture = Array3D<float>;
using VNormal = Array3D<float>;

using FaceIndex = Array3D<ssize_t>;
using Face = std::vector<FaceIndex>;

#endif  // PARSING_OBJ_WAVEFRONT_DATA_HPP
