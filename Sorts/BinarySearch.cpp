uint32_t SkinnedMesh::findInterpolatedIndex(IndexType pIndexType, float pAnimTicks, const aiNodeAnim* pAiNodeAnim)
{
	uint32_t numKeys = 0;

	switch (pIndexType)
	{
	case SkinnedMesh::IndexType::SCALING_INDEX:
		numKeys = pAiNodeAnim->mNumScalingKeys;
		break;
	case SkinnedMesh::IndexType::ROTATION_INDEX:
		numKeys = pAiNodeAnim->mNumRotationKeys;
		break;
	case SkinnedMesh::IndexType::POSITION_INDEX:
		numKeys = pAiNodeAnim->mNumPositionKeys;
		break;
	}
	
	if (numKeys <= 1)
		return 0;

	auto getNodeAnimTime = [&](IndexType pIndexType, uint32_t pIndex) -> float
		{
			switch (pIndexType)
			{
			case SkinnedMesh::IndexType::SCALING_INDEX:
				return pAiNodeAnim->mScalingKeys[pIndex].mTime;
			case SkinnedMesh::IndexType::ROTATION_INDEX:
				return pAiNodeAnim->mRotationKeys[pIndex].mTime;
			case SkinnedMesh::IndexType::POSITION_INDEX:
				return pAiNodeAnim->mPositionKeys[pIndex].mTime;
			}
			return 0.0f;
		};

	float firstKeyTime  = getNodeAnimTime(pIndexType, 0);
	float lastKeyTime = getNodeAnimTime(pIndexType, numKeys - 1);

	if (pAnimTicks <= firstKeyTime)
		return 0;
	if (pAnimTicks >= lastKeyTime)
		return numKeys - 2;

	uint32_t low = 0;
	uint32_t high = numKeys - 1;
	uint32_t result = 0;

	while (low <= high)
	{
		uint32_t mid = low + (high - low) / 2;
		float midKeyTime = getNodeAnimTime(pIndexType, mid);

		if (midKeyTime <= pAnimTicks)
		{
			float nextTime = getNodeAnimTime(pIndexType, mid + 1);
			if (pAnimTicks < nextTime)
			{
				result = mid;
				break;
			}

			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}

	return result;
}
