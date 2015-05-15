// Define a generic function to check if two shapes are intersecting
template<class T1, class T2> bool isIntersecting(T1 &obj1, T2 &obj2)
{
	return obj1.getRight() >= obj2.getLeft() && obj1.getLeft() <= obj2.getRight()
		&& obj1.getBottom() >= obj2.getTop() && obj1.getTop() <= obj2.getBottom();
}
