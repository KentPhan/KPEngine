GameObject = 
{
	name = "Monster",
	position = { 100.0, 2.0, 3.0},
	layer = 1,
	tag = 4,
	components =
	{
		KPRender2DComponent = 
		{
			texture = "Assets\\Sprites\\Characters\\zombie.dds"
		},
		KPPhysics2DComponent = 
		{
			isStatic=false
		},
		BoxCollisionComponent = 
		{
			center = { 0.0, 0.0, 0.0},
			extents = { 15.0, 15.0, 0.0}
		}
	}
}