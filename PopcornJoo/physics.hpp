#pragma once
#include <vector>
#include <memory>
#include <functional>

#include "circle.h"
#include "rectangle.h"
#include "object.h"
#include "collision.h"


namespace phy {
	class physicsEngine final {
	private:
		std::vector<std::shared_ptr<object>> target;
		std::vector<std::shared_ptr<object>> wall;
		std::vector<std::shared_ptr<object>> object;

	public:
		std::function<void(std::weak_ptr<phy::object>, std::weak_ptr<phy::object>)> collisionObject;
		
		void AddTarget(std::shared_ptr<phy::object> data) {
			target.push_back(data);
		}

		void AddWall(std::shared_ptr<phy::object> data) {
			wall.push_back(data);
		}

		void AddObject(std::shared_ptr<phy::object> data) {
			object.push_back(data);
		}

		void ClearObject() {
			target.clear();
			wall.clear();
			object.clear();
		}

		void update(long long tick) {
			
		}

	protected:



	};
}