Software Renderer
The Software Renderer is a real-time graphics engine that focuses on rendering 3D objects using the CPU rather than the GPU. It supports vertex and fragment shaders, with implementations of Gouraud and Phong shading models.

Key Features:
Vertex and Fragment Shading: Supports programmable shaders to modify vertex positions and colors in the rendering pipeline.
Lighting Models: Implements Gouraud and Phong shading techniques for simulating realistic lighting interactions.
Primitives Rendering: Renders basic geometric primitives such as spheres, cubes, and triangles.
Post-processing: Post-processing effects are applied after the scene is rendered to enhance the visual output.
SDL and glm Libraries: Utilizes SDL for window management and handling user input, while glm is used for mathematical operations like matrix transformations, vectors, and more.
Ray Tracer
The Ray Tracer is designed for realistic image synthesis by simulating the path of light rays as they interact with objects in a 3D scene. It can render both primitive and complex models with support for a variety of materials.

Key Features:
Primitive and Complex Model Rendering: Renders simple objects (e.g., spheres, planes) as well as complex 3D models.
Material Support: Implements a range of material types, including:
Lambertian: Diffuse reflection for matte surfaces.
Dielectric: Transparent materials, supporting refraction and reflection (e.g., glass).
Metallic: Reflective materials with sharp reflection (e.g., metal).
Anti-aliasing: Reduces jagged edges and pixelated artifacts using techniques like supersampling.
Multiple Bounce Reflections: Simulates light bounces, improving realism in reflections and refractions.
Libraries Used
SDL: A cross-platform library used for managing windows, graphics, and input, making it easier to handle tasks like creating a window and user interaction.
glm: A C++ mathematics library for graphics software, providing easy-to-use tools for working with matrices, vectors, and transformations.
Features

<img width="602" alt="SoftwareRenderer" src="https://github.com/user-attachments/assets/5d1a8498-c6ee-42be-b44c-8e91c15b231b">
Software Renderer:
Gouraud and Phong lighting models for realistic shading.
Basic rendering pipeline with vertex and fragment shaders.
Post-processing effects like bloom or depth of field (if applicable).

<img width="601" alt="RayTracer" src="https://github.com/user-attachments/assets/128d6437-e6fa-4b3e-8659-00bf6f3c1639">
Ray Tracer:
Support for different materials with realistic shading.
Anti-aliasing to enhance image quality.
Multiple bounces for reflections and refractions.
