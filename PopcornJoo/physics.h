#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <spdlog/spdlog.h>

#include "circle.h"
#include "rectangle.h"
#include "object.h"
#include "collision.h"


namespace phy {
	class physicsEngine final {
	private:
		std::vector<std::shared_ptr<object>> target;
		std::vector<std::shared_ptr<object>> wall;
		//std::vector<std::shared_ptr<object>> object;

	public:
		static std::unique_ptr<phy::physicsEngine> shared;

		std::function<void(std::weak_ptr<phy::object>, std::weak_ptr<phy::object>)> collisionObject;
		
		void AddTarget(std::shared_ptr<phy::object> data) {
			target.push_back(data);
		}

		void AddWall(std::shared_ptr<phy::object> data) {
			wall.push_back(data);
		}

		/*void AddObject(std::shared_ptr<phy::object> data) {
			object.push_back(data);
		}*/

		void ClearObject() {
			target.clear();
			wall.clear();
			//object.clear();
		}

		bool checkCollision(std::weak_ptr<phy::object> left, std::weak_ptr<phy::object> right) {
			auto ls = left.lock();
			auto rs = right.lock();
			if (!(ls && rs)) {
				return false;
			}
			double leftRadius = 0;
			grc::rect leftRect;
			double rightRadius = 0;
			grc::rect rightRect;
			
			auto leftType = ls->getType(leftRadius, leftRect);
			auto rightType = ls->getType(leftRadius, rightRect);

			if (leftType == phy::collisiontype::circle &&
				rightType == phy::collisiontype::circle) {
				auto length = (ls->transform - rs->transform).magnitude();
				if (length < leftRadius + rightRadius) {
					return true;
				}
				else {
					return false;
				}
			}

			spdlog::info("固备泅等 面倒 贸府");
			return false;

		}

		void update(long long tick) {
			for (auto& t : target) {
				t->update(tick);
			}

			for (auto& w : wall) {
				w->update(tick);
			}

			for (auto& t : target) {
				for (auto& w : wall) {
					bool data = checkCollision(t, w);
					if (data) {
						t->collisionevent(t->transform, w->transform);
						w->collisionevent(w->transform, t->transform);
					}

				}
			}


		}

	protected:

	};
}
