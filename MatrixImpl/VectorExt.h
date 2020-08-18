#pragma once
namespace stf
{
	template < typename Ty_Left, typename Ty_Right, size_t DIM >
	auto Dot(const Vec<DIM, Ty_Left>& vLeft, const Vec<DIM, Ty_Right>& vRight)
	{
		decltype(vLeft.x * vRight.x) Result = 0;
		for (int i = 0; i < tVec2; ++i)
			Result += vLeft[i] * vRight[i];
		return Result;
	}

	/* Utilities */
	template < class vTy >
	static tVec2<vTy> WorldToScreen(tVec2<vTy> world_point, tVec2<vTy> offset, tVec2<vTy> scale = { 1, 1 })
	{
		return (world_point - offset) * scale;
	}
	template < class vTy >
	static tVec2<vTy> ScreenToWorld(tVec2<vTy> screen_point, tVec2<vTy> offset, tVec2<vTy> scale = { 1, 1 })
	{
		return screen_point / scale + offset;
	}

	static tVec2<int> WorldToScreen(tVec2<int> world_point, tVec2<int> offset) { return world_point - offset; }
	static tVec2<int> ScreenToWorld(tVec2<int> screen_point, tVec2<int> offset) { return screen_point + offset; }
}




