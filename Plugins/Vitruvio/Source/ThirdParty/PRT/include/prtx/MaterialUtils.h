/*
  COPYRIGHT (c) 2012-2022 Esri R&D Center Zurich
  TRADE SECRETS: ESRI PROPRIETARY AND CONFIDENTIAL
  Unpublished material - all rights reserved under the
  Copyright Laws of the United States and applicable international
  laws, treaties, and conventions.

  For additional information, contact:
  Environmental Systems Research Institute, Inc.
  Attn: Contracts and Legal Services Department
  380 New York Street
  Redlands, California, 92373
  USA

  email: contracts@esri.com
*/

#ifndef SRC_PRTX_MATERIALUTILS_H_
#define SRC_PRTX_MATERIALUTILS_H_

#include "prtx/prtx.h"

#include "prtx/Material.h"

#include <string>
#include <vector>


namespace prtx {


/** @namespace prtx::MaterialUtils
 * @brief Utility functions for working with prtx::Material instances.
 */
namespace MaterialUtils {

/**
 * Converts the material to a set of CGA attributes, analogous the CGA @cgaref{func_getMaterial.html,getMaterial()} function.
 *
 * @param mat Material to convert.
 * @param changedOnly controls whether all attributes and their values are returned or only the ones which got changed, i.e. set via the CGA @cgaref{op_set.html,set()} operation or via an inserted asset.
 * @returns a vector of strings in the format { atr name 1, value1, attr name 2, value2, ...}
 *
 * \sa prtx::ShapeUtils::combineMaterials().
 *
 */

PRTX_EXPORTS_API std::vector<std::wstring> getMaterialAsCGAStrings(const prtx::Material& mat, bool changedOnly);

} // namespace MaterialUtils


} // namespace prtx

#endif /* SRC_PRTX_MATERIALUTILS_H_ */
