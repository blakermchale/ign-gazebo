/*
 * Copyright (C) 2021 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <gtest/gtest.h>

#include <ignition/msgs/joint_wrench.pb.h>

#include <ignition/common/Console.hh>
#include <ignition/common/Util.hh>
#include <ignition/math/Pose3.hh>
#include <ignition/transport/Node.hh>

#include "ignition/gazebo/components/ForceTorque.hh"

#include "ignition/gazebo/components/Name.hh"
#include "ignition/gazebo/components/Pose.hh"
#include "ignition/gazebo/components/Sensor.hh"

#include "ignition/gazebo/Server.hh"
#include "ignition/gazebo/SystemLoader.hh"
#include "ignition/gazebo/test_config.hh"

#include "../helpers/Relay.hh"

#define TOL 1e-4

using namespace ignition;
using namespace gazebo;

/// \brief Test ForceTorqueTest system
class ForceTorqueTest : public ::testing::Test
{
  // Documentation inherited
  protected: void SetUp() override
  {
    ignition::common::Console::SetVerbosity(4);
    ignition::common::setenv("IGN_GAZEBO_SYSTEM_PLUGIN_PATH",
           (std::string(PROJECT_BINARY_PATH) + "/lib").c_str());
  }
};

std::mutex mutex;
std::vector<msgs::Wrench> forceTorqueMsgs;

/////////////////////////////////////////////////
void forceTorqueCb(const msgs::Wrench &_msg)
{
  mutex.lock();
  forceTorqueMsgs.push_back(_msg);
  mutex.unlock();
}

