#include <cxxopts.hpp>
#include <fmt/color.h>
#include <fmt/core.h>
#include <iostream>
#include <spdlog/cfg/env.h>
#include <spdlog/spdlog.h>

#include "libsvg.hpp"

int main(int argc, char *argv[]) try {

  spdlog::cfg::load_env_levels();

  // =================================================================================================
  // CLI
  cxxopts::Options options(argv[0], "Description");
  options.positional_help("[optional args]").show_positional_help();

  // clang-format off
  options.add_options()
    ("h,help", "Print help")
    ("o,output", "Output filename (.svg)", cxxopts::value<std::string>())
    ("n", "n coef", cxxopts::value<int>())
    ("d", "d coef", cxxopts::value<int>())
    ("show_curve", "show complete curve", cxxopts::value<bool>()->default_value("false"))
    ("c,canvas", "Canvas Size", cxxopts::value<int>()->default_value("2000"))
    ;
  // clang-format on
  options.parse_positional({"output", "canvas", "n", "d"});
  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    return EXIT_SUCCESS;
  }

  const int canvasSize = result["canvas"].as<int>();
  const int n = result["n"].as<int>();
  const int d = result["d"].as<int>();
  const bool showCurve = result["show_curve"].as<bool>();
  const std::string filename = result["output"].as<std::string>();

  // =================================================================================================
  // Code
  svg::Document doc(canvasSize, canvasSize, svg::Color(0, 0, 0));
  const Point canvasCenter{canvasSize / 2.f, canvasSize / 2.f};
  const float scale = 500.f;
  std::vector<Line> lines;

  for (int theta = 0; theta < 360; ++theta) {

    // Maurer Rose
    {
      const float k1 = theta * d * pi / 180.f;
      const float r1 = scale * sin(n * k1);
      const Point pt1(r1 * cos(k1), r1 * sin(k1));

      const float k2 = (theta + 1) * d * pi / 180.f;
      const float r2 = scale * sin(n * k2);
      const Point pt2(r2 * cos(k2), r2 * sin(k2));

      doc.addLine({canvasCenter + pt1, canvasCenter + pt2}, {}, svg::Stroke{{0xffffff, 0.5f}, 2.f});
    }

    if (showCurve) {
      // Rose Curve
      const float k1 = theta * pi / 180.f;
      const float r1 = scale * sin(n * k1);
      const Point pt1(r1 * cos(k1), r1 * sin(k1));

      const float k2 = (theta + 1) * pi / 180.f;
      const float r2 = scale * sin(n * k2);
      const Point pt2(r2 * cos(k2), r2 * sin(k2));

      lines.emplace_back(canvasCenter + pt1, canvasCenter + pt2);
    }
  }
  if (showCurve)
    doc.addPath(lines, {}, svg::Stroke{{0xffffff, 1.f}, 3.f});

  if (!doc.save(filename))
    throw std::runtime_error(fmt::format("Failed to save svg file : {}", filename));

  return EXIT_SUCCESS;

} catch (const cxxopts::exceptions::exception &e) {
  spdlog::error("Command Line : {}", e.what());
  return EXIT_FAILURE;

} catch (const std::exception &e) {
  spdlog::error("{}", e.what());
  return EXIT_FAILURE;
}
