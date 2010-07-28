// kate: indent-mode cstyle; indent-width 4; tab-width 4; space-indent false;
// vim:ai ts=4 et
#pragma once

#include <QWidget>

#include <Geometry2d/Point.hpp>
#include <Geometry2d/TransformMatrix.hpp>
#include <protobuf/LogFrame.pb.h>

class Logger;

/** class that performs drawing of log data onto the field */
class FieldView : public QWidget
{
	public:
		FieldView(QWidget* parent = 0);
		
		void layerVisible(int i, bool value)
		{
			if (i >= 0 && i < _layerVisible.size())
			{
				_layerVisible[i] = value;
			}
		}
		
		bool layerVisible(int i) const
		{
			if (i < _layerVisible.size())
			{
				return true;
			} else {
				return false;
			}
		}
		
		void history(const std::vector<Packet::LogFrame> *value)
		{
			_history = value;
		}
		
		void rotate(int value);
		
		bool showRawRobots;
		bool showRawBalls;
		bool showCoords;
		
	protected:
		virtual void paintEvent(QPaintEvent* pe);
		virtual void resizeEvent(QResizeEvent *e);
		
		virtual void drawWorldSpace(QPainter &p);
		virtual void drawTeamSpace(QPainter &p);
		
		void drawText(QPainter& p, QPointF pos, QString text, bool center = true);
		void drawField(QPainter& p, const Packet::LogFrame &frame);
		void drawRobot(QPainter& p, bool blueRobot, int ID, QPointF pos, float theta, bool hasBall = false);
		void drawCoords(QPainter& p);

	protected:
		// Coordinate transformations
		Geometry2d::TransformMatrix _screenToWorld;
		Geometry2d::TransformMatrix _worldToTeam;
		Geometry2d::TransformMatrix _teamToWorld;
		
		// Rotation of the field in 90-degree increments (0 to 3).
		int _rotate;
		
		// How many degrees to rotate text so it shows up the right way on screen
		int _textRotation;
		
		const std::vector<Packet::LogFrame> *_history;
		
		QVector<bool> _layerVisible;
};