#include "ge/physics_controller.hpp"
#include "ge/world.hpp"

namespace ge
{
physics_controller::physics_controller(actor& actor_to_control) : m_actor{&actor_to_control}
{
	b2BodyDef body_def;
	body_def.active = true;
	body_def.userData = this;
	body_def.type = b2BodyType::b2_dynamicBody;

	m_b2_body = actor_to_control.get_world().m_b2_world.CreateBody(&body_def);

	actor_to_control.signal_transform_changed.connect([this](actor& act)
		{
			auto tmp = act.calcuate_absolute_location();

			m_b2_body->SetTransform({tmp.x, tmp.y}, act.calcuate_absolute_rotation());
		});

	actor_to_control.get_world().signal_update.connect([this](float)
		{
			auto trans = m_b2_body->GetTransform();
			
			m_actor->set_absolute_location({trans.p.x, trans.p.y});
			m_actor->set_absolute_rotation(trans.q.GetAngle());
			
		});
}
physics_controller::~physics_controller()
{
	m_actor->get_world().m_b2_world.DestroyBody(m_b2_body);
}
}
