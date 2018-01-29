sort(v.begin(), v.end());
	for (i = v.begin(); i < v.end() - 1; i++)
	{
		for (j = i + 1; j < v.end(); j++)
		{
			if (binary_search(v.begin(), v.end(), Point(j->x, i->y)) &&
				binary_search(v.begin(), v.end(), Point(i->x, j->y)) &&
				i->x != j->x &&
				i->y != j->y )
			{
				nTotalNum++;
			}
		}
	}
	cout << nTotalNum / 2;