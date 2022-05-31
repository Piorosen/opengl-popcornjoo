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

		bool rectCheck(grc::rect leftRect, grc::rect rightRect, collisioninfo& info) {
			if (leftRect.location.x + leftRect.size.width >= rightRect.location.x &&
				leftRect.location.x <= rightRect.location.x + rightRect.size.width &&
				leftRect.location.y + leftRect.size.height >= rightRect.location.y &&
				leftRect.location.y <= rightRect.location.y + rightRect.size.height) {
				info.own.push_back(phy::collisionPos::none);

				auto radius = (leftRect.size.width);

				auto pos = leftRect.center();
				double left = abs(pos.x - rightRect.location.x);
				double top = abs(pos.y - rightRect.location.y);
				double right = abs((rightRect.location.x + rightRect.size.width) - pos.x);
				double bottom = abs((rightRect.location.y + rightRect.size.height) - pos.y);
				spdlog::info("{}, {}, {}, {}", left, top, right, bottom);

				if (left < top) {
					info.other.push_back(phy::collisionPos::left);
				}
				if (top < radius) {
					info.other.push_back(phy::collisionPos::top);
				}
				if (right < radius) {
					info.other.push_back(phy::collisionPos::right);
				}
				{
					info.other.push_back(phy::collisionPos::bottom);
				}

				return true;
			}
			else {
				return false;
			}
		}

		bool checkCollision(phy::collisiontype leftType, grc::rect leftRect, double leftRadius, phy::vector2d leftPos,
						    phy::collisiontype rightType, grc::rect rightRect, double rightRadius, phy::vector2d rightPos,
							collisioninfo& info) {
			auto lst = leftPos;
			auto rst = rightPos;

			if (leftType == phy::collisiontype::circle &&
				rightType == phy::collisiontype::circle) {
				info.type = collidetype::circleTocircle;

				auto length = (lst - rst).magnitude();
				if (length < leftRadius + rightRadius) {
					return true;
				}
				else {
					return false;
				}
			}

			else if (leftType == phy::collisiontype::circle && rightType == phy::collisiontype::rectangle) {
				leftRect.location.x += lst.x;
				leftRect.location.y += lst.y;

				rightRect.location.x += rst.x;
				rightRect.location.y += rst.y;

				if (leftType != rightType) {
					info.type = collidetype::circleToRect;
					return rectCheck(leftRect, rightRect, info);
				}
				else {
					info.type = collidetype::RectToRect;
					spdlog::info("固备泅等 面倒 贸府");
					return false;
				}
			}
		}
		
		bool nextPosVel(std::weak_ptr<phy::object> left, std::weak_ptr<phy::object> right, collisioninfo& info) {
			auto ls = left.lock();
			auto rs = right.lock();

			double ld;
			grc::rect lr;
			double rd;
			grc::rect rr;

			auto lsType = ls->getType(ld, lr);
			auto rsType = rs->getType(rd, rr);

			auto target = ls->getTransform();
			auto start = ls->getOldTransform();
			auto length = (target - start);
			auto base = (target - start).normalization() * ld;
			//int i;
			//for (i = 0; i < (int)(length.x / base.x); i++) {
			//	bool d = checkCollision(lsType, lr, ld, start + (base * i), 
			//							rsType, rr, rd, rs->getTransform(), info);
			//	if (d == true) {
			//		spdlog::info("coolide");
			//		return true;
			//		break;
			//	}
			//}
			auto result = checkCollision(lsType, lr, ld, target,
										 rsType, rr, rd, rs->getTransform(), info);

			return result;
		}

		void update(long long tick) {
			for (auto& t : target) {
				if (t->getHidden()) {
					continue;
				}
				t->update(tick);
				for (auto& w : wall) {
					if (w->getHidden()) {
						continue;
					}
					w->update(tick);
					collisioninfo info{};
					bool data = nextPosVel(t, w, info);
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
