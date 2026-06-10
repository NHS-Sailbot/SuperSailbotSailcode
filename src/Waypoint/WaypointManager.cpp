//
// Created by sailbot on 6/10/25.
//

#include "WaypointManager.h"

namespace Waypoints{
  // TODO: this should be replaced with a same schema and no data once you properly get the runtime sending working.
  const char* WaypointManager::json = R"json(
{
  "waypoints": [
    {
      "lat": 42.46979399273758,
      "lng": -76.50480866432191
    },
    {
      "lat": 42.4689155383634,
      "lng": -76.50734066963196
    },
    {
      "lat": 42.46778381770969,
      "lng": -76.50668621063234
    },
    {
      "lat": 42.468021243319036,
      "lng": -76.5036177635193
    },
    {
      "lat": 42.46931915406623,
      "lng": -76.50304913520814
    }
  ],
  "buoys": [],
  "restrictedArea": [
    {
      "lat": 42.470688262455,
      "lng": -76.50445461273195
    },
    {
      "lat": 42.46931124005786,
      "lng": -76.5094006061554
    },
    {
      "lat": 42.46672330566013,
      "lng": -76.50771617889406
    },
    {
      "lat": 42.46803707166098,
      "lng": -76.50210499763489
    },
    {
      "lat": 42.46913713162049,
      "lng": -76.50280237197876
    },
    {
      "lat": 42.469651541514395,
      "lng": -76.50312423706055
    },
    {
      "lat": 42.469825648520924,
      "lng": -76.50314569473267
    },
    {
      "lat": 42.470245086138895,
      "lng": -76.50360703468324
    }
  ]
}
)json";
};