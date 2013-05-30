/*
 * Copyright (c) 2013, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* Author: Acorn Pooley */

#ifndef COLLISION_DISTANCE_FIELD_DISPLAY_DF_LINK_H
#define COLLISION_DISTANCE_FIELD_DISPLAY_DF_LINK_H

#include <rviz/robot/robot.h>
#include <rviz/robot/robot_link.h>
#include <eigen_stl_containers/eigen_stl_containers.h>

namespace rviz
{
class ColorProperty;
class FloatProperty;
class IntProperty;
class EnumProperty;
class EditableEnumProperty;
}

namespace moveit_rviz_plugin
{
class CollisionDistanceFieldDisplay;
class PerLinkSubObjBase;

// extra per-link properties to display
class DFLink : public rviz::RobotLink
{
Q_OBJECT
public:
  DFLink( rviz::Robot* robot,
          const urdf::LinkConstPtr& link,
          const std::string& parent_joint_name,
          bool visual,
          bool collision,
          CollisionDistanceFieldDisplay *display);
  virtual ~DFLink();

  virtual void hideSubProperties(bool hide);

  CollisionDistanceFieldDisplay *getDisplay() const { return display_; }

  void getLinkSpheres(EigenSTL::vector_Vector3d& centers, std::vector<double>& radii) const;


public Q_SLOTS:
  void updateSampleProp();

protected:
  // sample property
  rviz::BoolProperty* sample_prop_;
  CollisionDistanceFieldDisplay *display_;
  std::vector<PerLinkSubObjBase*> per_link_objects_;
};


class DFLinkFactory : public rviz::Robot::LinkFactory
{
public:
  DFLinkFactory(CollisionDistanceFieldDisplay *display);

  virtual rviz::RobotLink* createLink( rviz::Robot* robot,
                                 const boost::shared_ptr<const urdf::Link>& link,
                                 const std::string& parent_joint_name,
                                 bool visual,
                                 bool collision);
private:
  CollisionDistanceFieldDisplay *display_;
};


}

#endif
