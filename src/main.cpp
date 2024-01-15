#include <iostream>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_handles.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int main(void)
{
    if (glfwInit() == false) {
        std::cerr << "Failed to initialize GLFW.\n";
        std::exit(1);
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow *window
        = glfwCreateWindow(800, 600, "WHAT YOU WANT", nullptr, nullptr);

    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window.\n";
        std::exit(1);
    }

    vk::ApplicationInfo app_info {};
    app_info.setApiVersion(vk::ApiVersion13);
    app_info.setPEngineName("Astera on a swing");
    app_info.setEngineVersion(vk::makeApiVersion(0, 0, 1, 0));
    app_info.setPApplicationName("BFM");
    app_info.sType = vk::StructureType::eApplicationInfo;

    /* instance create info */
    vk::InstanceCreateInfo instance_create_info {};
    instance_create_info.setPApplicationInfo(&app_info);
    instance_create_info.sType = vk::StructureType::eInstanceCreateInfo;

    uint32_t glfw_ext_count = 0;
    const char **glfw_ext;

    glfw_ext = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

    instance_create_info.setEnabledExtensionCount(glfw_ext_count);
    instance_create_info.setPpEnabledExtensionNames(glfw_ext);
    /* instance create info end */

    /* extensions */
    uint32_t extension_count = 0;
    vk::Result res = vk::enumerateInstanceExtensionProperties(
        nullptr, &extension_count, nullptr);

    if (res != vk::Result::eSuccess) {
        std::cerr << "no extensions?\n";
        std::exit(1);
    }

    std::vector<vk::ExtensionProperties> extensions(extension_count);
    if (vk::enumerateInstanceExtensionProperties(
            nullptr, &extension_count, extensions.data())
        != vk::Result::eSuccess) {
        std::cerr << "extension error :fr:\n";
        std::exit(1);
    }

    std::cout << "available extensions:\n";

    for (const auto &extension : extensions) {
        std::cout << '\t' << extension.extensionName << '\n';
    }

    /* end of extensions */

    // imagine needing to release shit :moyai:
    vk::UniqueInstance instance
        = vk::createInstanceUnique(instance_create_info);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    return 0;
}
