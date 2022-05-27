#pragma once
#include <list>
#include <memory>

#include "circle.h"
#include "rectangle.h"
#include "object.h"
#include "collision.h"

#include "EventHandler.h"

namespace phy {
	class physicsEngine final {
	private:
		std::list<std::shared_ptr<object>> collide;

	public:
		grc::EventHandler<std::weak_ptr<object>, std::weak_ptr<object>> collisionObject;
		
		void AddObject(std::shared_ptr<object> data) {
			collide.push_back(data);
		}

		void RemoveObject(std::shared_ptr<object> data) {
			for (auto& p : collide) {
				collide.remove(data);
			}
		}

		void ClearObject() {
			collide.clear();
		}

		void update(long long tick) {
			
		}

	protected:



	};
}