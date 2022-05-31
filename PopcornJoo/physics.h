#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <spdlog/spdlog.h>

#include "circle.h"
#include "rectangle.h"
#include "object.h"
#include "collision.h"
#include "collisioninfo.h"


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

		bool checkCollision(std::weak_ptr<phy::object> left, std::weak_ptr<phy::object> right, collisioninfo& info) {
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
			auto rightType = rs->getType(leftRadius, rightRect);

			if (leftType == phy::collisiontype::circle &&
				rightType == phy::collisiontype::circle) {
				info.type = collidetype::circleTocircle;

				auto length = (ls->transform - rs->transform).magnitude();
				if (length < leftRadius + rightRadius) {
					return true;
				}
				else {
					return false;
				}
			}
			else if (leftType == phy::collisiontype::circle && rightType == phy::collisiontype::rectangle) {
				leftRect.location.x += ls->transform.x;
				leftRect.location.y += ls->transform.y;

				rightRect.location.x += rs->transform.x;
				rightRect.location.y += rs->transform.y;

				if (leftType != rightType) {
					info.type = collidetype::circleToRect;
				}
				else {
					info.type = collidetype::RectToRect;
					spdlog::info("固备泅等 面倒 贸府");
					return false;
				}
				
				if (leftRect.location.x + leftRect.size.width >= rightRect.location.x &&
					leftRect.location.x <= rightRect.location.x + rightRect.size.width &&
					leftRect.location.y + leftRect.size.height >= rightRect.location.y &&
					leftRect.location.y <= rightRect.location.y + rightRect.size.height) {
					
					info.own = phy::collisionPos::none;

					auto pos = leftRect.center();
					double left = abs(pos.x - rightRect.location.x);
					double top = abs(pos.y - rightRect.location.y);
					double right = abs((rightRect.location.x + rightRect.size.width) - pos.x);
					double bottom = abs((rightRect.location.y + rightRect.size.height) - pos.y);
					spdlog::info("{}, {}, {}, {}", left, top, right, bottom);

					if (left < top && left < right && left < bottom) {
						info.other = phy::collisionPos::left;
					}
					else if (top < left && top < right && top < bottom) {
						info.other = phy::collisionPos::top;
					}
					else if (right < top && right < left && right < bottom) {
						info.other = phy::collisionPos::right;
					}
					else {
						info.other = phy::collisionPos::bottom;
					}

					return true;
				}
				else {
					return false;
				}
			}


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
					collisioninfo info{};
					bool data = checkCollision(t, w, info);
					if (data) {
						if (t->collisionevent) {
							t->collisionevent(t, w, info, tick);
						}
						collisioninfo info2 = info;
						info2.other = info.own;
						info2.own = info.other;
						if (w->collisionevent) {
							w->collisionevent(w, t, info2, tick);
						}
					}
				}
			}
		}

	protected:

	};
}
