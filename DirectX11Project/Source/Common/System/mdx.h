//==========================================================================
// masyo no dx11 [mdx.h]
// author : MasyoLab
//==========================================================================
#pragma once

// NAMESPACE
#pragma region namespace group

#define _MDX_BEGIN namespace mdx {
#define _MDX_END }
#define _MDX ::mdx::

_MDX_BEGIN
namespace system {}
namespace object {}
namespace component {}
namespace structure {}
namespace shared_constant {}
_MDX_END

#define _MDX_SYSTEM_BEGIN namespace mdx::system {
#define _MDX_SYSTEM_END }
#define _MDX_SYSTEM_ ::mdx::system::

#define _MDX_OBJECT_BEGIN namespace mdx::object {
#define _MDX_OBJECT_END }
#define _MDX_OBJECT_ ::mdx::object::

#define _MDX_COMPONENT_BEGIN namespace mdx::component {
#define _MDX_COMPONENT_END }
#define _MDX_COMPONENT_ ::mdx::component::

#define _MDX_STRUCTURE_BEGIN namespace mdx::structure {
#define _MDX_STRUCTURE_END }
#define _MDX_STRUCTURE_ ::mdx::structure::

#define _MDX_SHARED_CONSTANT_BEGIN namespace mdx::shared_constant {
#define _MDX_SHARED_CONSTANT_END }
#define _MDX_SHARED_CONSTANT_ ::mdx::shared_constant::

#define _MDX_COMMON_BEGIN namespace mdx::common {
#define _MDX_COMMON_END }
#define _MDX_COMMON_ ::mdx::common::

#define _MDX_USING using namespace mdx;
#define _MDX_USING_SYSTEM using namespace mdx::system;
#define _MDX_USING_OBJECT using namespace mdx::object;
#define _MDX_USING_COMPONENT using namespace mdx::component;
#define _MDX_USING_STRUCTURE using namespace mdx::structure;
#define _MDX_USING_SHARED_CONSTANT using namespace mdx::shared_constant;
#define _MDX_USING_COMMON using namespace mdx::common;

#pragma endregion