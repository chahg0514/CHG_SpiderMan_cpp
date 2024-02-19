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

// !! DO NOT MODIFY !! - this file is automatically generated by CGAC
// Fri Aug 26 17:34:03 CEST 2022

#ifndef BUILTINMATERIALATTRIBUTES_H_
#define BUILTINMATERIALATTRIBUTES_H_

#include "prtx/prtx.h"
#include "prtx/Texture.h"
#include "prtx/BuiltinAttributes.h"

#include <string>
#include <vector>


namespace prtx {

/**
 * Interface for direct getters of the CGA material.* attributes. There are also direct getters for the
 * default shader keys.
 * @sa Material
 */
class PRTX_EXPORTS_API BuiltinMaterialAttributes : public BuiltinAttributesGetters {
public:

	// cga attributes
	virtual double ambient_b() const = 0;
	virtual double ambient_g() const = 0;
	virtual double ambient_r() const = 0;
	virtual double bumpValue() const = 0;
	virtual double bumpmap_rw() const = 0;
	virtual double bumpmap_su() const = 0;
	virtual double bumpmap_sv() const = 0;
	virtual double bumpmap_tu() const = 0;
	virtual double bumpmap_tv() const = 0;
	virtual double color_b() const = 0;
	virtual double color_g() const = 0;
	virtual double color_r() const = 0;
	virtual double colormap_rw() const = 0;
	virtual double colormap_su() const = 0;
	virtual double colormap_sv() const = 0;
	virtual double colormap_tu() const = 0;
	virtual double colormap_tv() const = 0;
	virtual double dirtmap_rw() const = 0;
	virtual double dirtmap_su() const = 0;
	virtual double dirtmap_sv() const = 0;
	virtual double dirtmap_tu() const = 0;
	virtual double dirtmap_tv() const = 0;
	virtual double emissive_b() const = 0;
	virtual double emissive_g() const = 0;
	virtual double emissive_r() const = 0;
	virtual double emissivemap_rw() const = 0;
	virtual double emissivemap_su() const = 0;
	virtual double emissivemap_sv() const = 0;
	virtual double emissivemap_tu() const = 0;
	virtual double emissivemap_tv() const = 0;
	virtual double metallic() const = 0;
	virtual double metallicmap_rw() const = 0;
	virtual double metallicmap_su() const = 0;
	virtual double metallicmap_sv() const = 0;
	virtual double metallicmap_tu() const = 0;
	virtual double metallicmap_tv() const = 0;
	virtual double normalmap_rw() const = 0;
	virtual double normalmap_su() const = 0;
	virtual double normalmap_sv() const = 0;
	virtual double normalmap_tu() const = 0;
	virtual double normalmap_tv() const = 0;
	virtual double occlusionmap_rw() const = 0;
	virtual double occlusionmap_su() const = 0;
	virtual double occlusionmap_sv() const = 0;
	virtual double occlusionmap_tu() const = 0;
	virtual double occlusionmap_tv() const = 0;
	virtual double opacity() const = 0;
	virtual double opacitymap_cutoff() const = 0;
	virtual double opacitymap_rw() const = 0;
	virtual double opacitymap_su() const = 0;
	virtual double opacitymap_sv() const = 0;
	virtual double opacitymap_tu() const = 0;
	virtual double opacitymap_tv() const = 0;
	virtual double reflectivity() const = 0;
	virtual double roughness() const = 0;
	virtual double roughnessmap_rw() const = 0;
	virtual double roughnessmap_su() const = 0;
	virtual double roughnessmap_sv() const = 0;
	virtual double roughnessmap_tu() const = 0;
	virtual double roughnessmap_tv() const = 0;
	virtual double shininess() const = 0;
	virtual double specular_b() const = 0;
	virtual double specular_g() const = 0;
	virtual double specular_r() const = 0;
	virtual double specularmap_rw() const = 0;
	virtual double specularmap_su() const = 0;
	virtual double specularmap_sv() const = 0;
	virtual double specularmap_tu() const = 0;
	virtual double specularmap_tv() const = 0;
	virtual const std::wstring& bumpmap() const = 0;
	virtual const std::wstring& colormap() const = 0;
	virtual const std::wstring& dirtmap() const = 0;
	virtual const std::wstring& emissivemap() const = 0;
	virtual const std::wstring& metallicmap() const = 0;
	virtual const std::wstring& name() const = 0;
	virtual const std::wstring& normalmap() const = 0;
	virtual const std::wstring& occlusionmap() const = 0;
	virtual const std::wstring& opacitymap() const = 0;
	virtual const std::wstring& opacitymap_mode() const = 0;
	virtual const std::wstring& roughnessmap() const = 0;
	virtual const std::wstring& shader() const = 0;
	virtual const std::wstring& specularmap() const = 0;

	// default Material keys
	virtual const std::vector<double>& ambientColor() const = 0;
	virtual const std::vector<double>& diffuseColor() const = 0;
	virtual const std::vector<double>& emissiveColor() const = 0;
	virtual const std::vector<double>& specularColor() const = 0;
	virtual const std::vector<prtx::TexturePtr>& bumpMap() const = 0;
	virtual const std::vector<prtx::TexturePtr>& diffuseMap() const = 0;
	virtual const std::vector<prtx::TexturePtr>& emissiveMap() const = 0;
	virtual const std::vector<prtx::TexturePtr>& metallicMap() const = 0;
	virtual const std::vector<prtx::TexturePtr>& normalMap() const = 0;
	virtual const std::vector<prtx::TexturePtr>& occlusionMap() const = 0;
	virtual const std::vector<prtx::TexturePtr>& opacityMap() const = 0;
	virtual const std::vector<prtx::TexturePtr>& roughnessMap() const = 0;
	virtual const std::vector<prtx::TexturePtr>& specularMap() const = 0;


protected:
	virtual void fillBuiltinKeys(WStringVector& keys) const override;
	virtual prt::Attributable::PrimitiveType getBuiltinType(const std::wstring& k) const override;

	virtual bool getBuiltinBool(const std::wstring& k, bool& stat) const override;
	virtual double getBuiltinFloat(const std::wstring& k, bool& stat) const override;
	virtual const std::wstring& getBuiltinString(const std::wstring& k, bool& val) const override;

	BuiltinMaterialAttributes() {};
	virtual ~BuiltinMaterialAttributes() {};
};


/**
 * Interface for direct setters of the CGA material.* attributes. There are also direct getters for the
 * default shader keys.
 * @sa MaterialBuilder
 */
class PRTX_EXPORTS_API BuiltinMaterialAttributesBuilder : public BuiltinAttributesSetters {
public:

	// cga attributes
	virtual void ambient_b(double val) = 0;
	virtual void ambient_g(double val) = 0;
	virtual void ambient_r(double val) = 0;
	virtual void bumpValue(double val) = 0;
	virtual void bumpmap_rw(double val) = 0;
	virtual void bumpmap_su(double val) = 0;
	virtual void bumpmap_sv(double val) = 0;
	virtual void bumpmap_tu(double val) = 0;
	virtual void bumpmap_tv(double val) = 0;
	virtual void color_b(double val) = 0;
	virtual void color_g(double val) = 0;
	virtual void color_r(double val) = 0;
	virtual void colormap_rw(double val) = 0;
	virtual void colormap_su(double val) = 0;
	virtual void colormap_sv(double val) = 0;
	virtual void colormap_tu(double val) = 0;
	virtual void colormap_tv(double val) = 0;
	virtual void dirtmap_rw(double val) = 0;
	virtual void dirtmap_su(double val) = 0;
	virtual void dirtmap_sv(double val) = 0;
	virtual void dirtmap_tu(double val) = 0;
	virtual void dirtmap_tv(double val) = 0;
	virtual void emissive_b(double val) = 0;
	virtual void emissive_g(double val) = 0;
	virtual void emissive_r(double val) = 0;
	virtual void emissivemap_rw(double val) = 0;
	virtual void emissivemap_su(double val) = 0;
	virtual void emissivemap_sv(double val) = 0;
	virtual void emissivemap_tu(double val) = 0;
	virtual void emissivemap_tv(double val) = 0;
	virtual void metallic(double val) = 0;
	virtual void metallicmap_rw(double val) = 0;
	virtual void metallicmap_su(double val) = 0;
	virtual void metallicmap_sv(double val) = 0;
	virtual void metallicmap_tu(double val) = 0;
	virtual void metallicmap_tv(double val) = 0;
	virtual void normalmap_rw(double val) = 0;
	virtual void normalmap_su(double val) = 0;
	virtual void normalmap_sv(double val) = 0;
	virtual void normalmap_tu(double val) = 0;
	virtual void normalmap_tv(double val) = 0;
	virtual void occlusionmap_rw(double val) = 0;
	virtual void occlusionmap_su(double val) = 0;
	virtual void occlusionmap_sv(double val) = 0;
	virtual void occlusionmap_tu(double val) = 0;
	virtual void occlusionmap_tv(double val) = 0;
	virtual void opacity(double val) = 0;
	virtual void opacitymap_cutoff(double val) = 0;
	virtual void opacitymap_rw(double val) = 0;
	virtual void opacitymap_su(double val) = 0;
	virtual void opacitymap_sv(double val) = 0;
	virtual void opacitymap_tu(double val) = 0;
	virtual void opacitymap_tv(double val) = 0;
	virtual void reflectivity(double val) = 0;
	virtual void roughness(double val) = 0;
	virtual void roughnessmap_rw(double val) = 0;
	virtual void roughnessmap_su(double val) = 0;
	virtual void roughnessmap_sv(double val) = 0;
	virtual void roughnessmap_tu(double val) = 0;
	virtual void roughnessmap_tv(double val) = 0;
	virtual void shininess(double val) = 0;
	virtual void specular_b(double val) = 0;
	virtual void specular_g(double val) = 0;
	virtual void specular_r(double val) = 0;
	virtual void specularmap_rw(double val) = 0;
	virtual void specularmap_su(double val) = 0;
	virtual void specularmap_sv(double val) = 0;
	virtual void specularmap_tu(double val) = 0;
	virtual void specularmap_tv(double val) = 0;
	virtual void name(const std::wstring& val) = 0;
	virtual void opacitymap_mode(const std::wstring& val) = 0;
	virtual void shader(const std::wstring& val) = 0;

	// default Material keys
	virtual void ambientColor(const std::vector<double>& val) = 0;
	virtual void diffuseColor(const std::vector<double>& val) = 0;
	virtual void emissiveColor(const std::vector<double>& val) = 0;
	virtual void specularColor(const std::vector<double>& val) = 0;
	virtual void bumpMap(const std::vector<prtx::TexturePtr>& val, const std::vector<std::wstring>& resolveMapKeys) = 0;
	virtual void diffuseMap(const std::vector<prtx::TexturePtr>& val, const std::vector<std::wstring>& resolveMapKeys) = 0;
	virtual void emissiveMap(const std::vector<prtx::TexturePtr>& val, const std::vector<std::wstring>& resolveMapKeys) = 0;
	virtual void metallicMap(const std::vector<prtx::TexturePtr>& val, const std::vector<std::wstring>& resolveMapKeys) = 0;
	virtual void normalMap(const std::vector<prtx::TexturePtr>& val, const std::vector<std::wstring>& resolveMapKeys) = 0;
	virtual void occlusionMap(const std::vector<prtx::TexturePtr>& val, const std::vector<std::wstring>& resolveMapKeys) = 0;
	virtual void opacityMap(const std::vector<prtx::TexturePtr>& val, const std::vector<std::wstring>& resolveMapKeys) = 0;
	virtual void roughnessMap(const std::vector<prtx::TexturePtr>& val, const std::vector<std::wstring>& resolveMapKeys) = 0;
	virtual void specularMap(const std::vector<prtx::TexturePtr>& val, const std::vector<std::wstring>& resolveMapKeys) = 0;


protected:
	// BuiltinAttributesSetters interface
	virtual bool setBuiltinBool(const std::wstring& k, bool val);
	virtual bool setBuiltinFloat(const std::wstring& k, double val);
	virtual bool setBuiltinString(const std::wstring& k, const std::wstring& found);
	
	BuiltinMaterialAttributesBuilder() {};
	virtual ~BuiltinMaterialAttributesBuilder() {};
};

}	// namespace
#endif 
