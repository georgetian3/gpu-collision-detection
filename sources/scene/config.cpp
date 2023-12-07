// #include <scene.hpp>
// #include <filesystem>
// #include <fstream>
// #include <string>

// #include <json.hpp>
// using json = nlohmann::json;

// const std::string defaultConfigString = R"(
// {
//     "mouseSensitivity": 0.1,
//     "camera": {
//         "speed": 10.0,
//         "position": [0, 0, 0] // position is a 3-tuple of floats/ints [x, y, z]
//     },
//     "lightSource": {
//         "speed": 10.0,
//         "position": [0, 0, 0],
//         "color": [1, 1, 1] // color is a 3-tuple of floats [r, g, b], each in the range [0, 1]
//     },
//     "models": [
//         {
//             "file": "/Users/george/repos/opengl-realistic/build/realistic-scene/resources/",
//             "position": [1.0, 1.0, 1.0],
//         }
//     ]
// }
// )";



// glm::dvec4 vectorToVec4(const std::vector<double>& fs) {
//     return glm::dvec4(fs[0], fs[1], fs[2], fs.size() == 4 ? fs[3] : 1.0);
// }

// glm::dvec3 vectorToVec3(const std::vector<double>& fs) {
//     return glm::dvec3(fs[0], fs[1], fs[2]);
// }

// bool Scene::loadConfig(std::filesystem::path configPath) {
//     configPath = makeAbsolute(configPath);
//     std::cout << "Config path: " << configPath << '\n';
//     try {
//         std::ifstream configFile(configPath);
//         config = json::parse(configFile, nullptr, true, true);
//         camera.setSensitivity(config.value("mouseSensitivity", 0.1));
//         camera.setSpeed(config.value("/camera/speed"_json_pointer, 10.0));
//         camera.setPosition(vectorToVec3(config.value("/camera/position"_json_pointer, std::vector<double>{0, 0, 10})));
//         lightSpeed = config.value("/lightSource/speed"_json_pointer, 10.0);
//         lightSource.setPosition(vectorToVec3(config.value("/lightSource/position"_json_pointer, std::vector<double>{0, 0, 0})));
//         lightConstant = config.value("/lightSource/constant"_json_pointer, 0.4);
//         lightLinear = config.value("/lightSource/linear"_json_pointer, 0.05);
//         lightQuadratic = config.value("/lightSource/quadratic"_json_pointer, 0.001);
//         lightAmbient = config.value("/lightSource/ambient"_json_pointer, 0.5);
//         lightDiffuse = config.value("/lightSource/diffuse"_json_pointer, 0.4);
//         lightSpecular = config.value("/lightSource/specular"_json_pointer, 0.1);

//         auto jsonModels = config.at("models").get<std::vector<json>>();
//         if (jsonModels.size() == 0) {
//             std::cout << "No models\n";
//         }
//         for (const auto& jsonModel: jsonModels) {
//             std::filesystem::path modelPath = makeAbsolute(static_cast<std::string>(jsonModel.at("path")));
//             std::cout << "Loading model: " << modelPath << '\n';
//             Model model;
//             model.name = jsonModel.value("name", "Unnamed model");
//             model.load(modelPath);
//             model.setPosition(vectorToVec3(jsonModel.value("position", std::vector<double>{0, 0, 0})));
//             model.setScale(jsonModel.value("scale", 1.0));
//             if (jsonModel.value("reflective", false)) {
//                 model.setSurfaceProperty(SP_REFLECTIVE);
//             } else if (jsonModel.value("refractive", false)) {
//                 model.setSurfaceProperty(SP_REFRACTIVE);
//             }
//             if (jsonModel.contains("color")) {
//                 model.setUseColor(true);
//                 model.setColor(vectorToVec4(jsonModel["color"]));
//             }
//             models.push_back(model);
//         }
//         std::cout << "Model loading complete!\n";
//     } catch (const json::parse_error& e) {
//         std::cerr << "Config does not exist/unreadable/contains invalid JSON: " << e.what() << '\n';
//         exit(1);
//     } catch (const json::type_error& e) {
//         std::cerr << "Config contains type error: " << e.what() << '\n';
//         exit(1);
//     } catch (const json::out_of_range& e) {
//         std::cerr << "Missing key: " << e.what() << '\n';
//         exit(1);
//     }
//     return true;
// }