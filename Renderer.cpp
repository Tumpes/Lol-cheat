#include <algorithm>
#include "Renderer.h"

float projMatrix[16] = { 0 };
float viewMatrix[16] = { 0 };
int width = 0;
int height = 0;

void Read(HANDLE hProcess, uint64_t addr, void* structure, int size) {
	SIZE_T bytesRead = 0;

	//Nt_ReadMemory(hProcess, (uint64_t*)addr, structure, size, &bytesRead);

	ReadProcessMemory(hProcess, (uint64_t*)addr, structure, size, &bytesRead);
}

/* Multiply two matrices */
void GameRenderer::MultiplyMatrices(float* out, float* a, int row1, int col1, float* b, int row2, int col2) {
	int size = row1 * col2;
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col2; j++) {
			float sum = 0.f;
			for (int k = 0; k < col1; k++)
				sum = sum + a[i * col1 + k] * b[k * col2 + j];
			out[i * col2 + j] = sum;
		}
	}
}

void GameRenderer::LoadFromMem() {

	char buff[128];
	memcpy(buff, *reinterpret_cast<void**>(Globals::BaseAddress + oRenderer), 128);
	memcpy(&width, &buff[oRendererWidth], sizeof(int));
	memcpy(&height, &buff[oRendererHeight], sizeof(int));

	const uint64_t ViewProjMatricesptr = (uint64_t)(Globals::BaseAddress + oViewProjMatrices);

	//std::cout << std::hex << moduleBase << std::endl;
	//std::cout << std::hex << OffsetViewProjMatrices << std::endl;

	memcpy(buff, (void*)ViewProjMatricesptr, 128);
	memcpy(viewMatrix, buff, 16 * sizeof(float));
	memcpy(projMatrix, &buff[16 * sizeof(float)], 16 * sizeof(float));
	MultiplyMatrices(viewProjMatrix, viewMatrix, 4, 4, projMatrix, 4, 4);
}



Vector2 GameRenderer::WorldToScreen(const Vector3 pos) {

	GameRenderer::LoadFromMem();

	Vector2 out = { 0.f, 0.f };
	Vector2 screen = { (float)width, (float)height };
	static Vector4 clipCoords;
	clipCoords.x = pos.x * viewProjMatrix[0] + pos.y * viewProjMatrix[4] + pos.z * viewProjMatrix[8] + viewProjMatrix[12];
	clipCoords.y = pos.x * viewProjMatrix[1] + pos.y * viewProjMatrix[5] + pos.z * viewProjMatrix[9] + viewProjMatrix[13];
	clipCoords.z = pos.x * viewProjMatrix[2] + pos.y * viewProjMatrix[6] + pos.z * viewProjMatrix[10] + viewProjMatrix[14];
	clipCoords.w = pos.x * viewProjMatrix[3] + pos.y * viewProjMatrix[7] + pos.z * viewProjMatrix[11] + viewProjMatrix[15];

	if (clipCoords.w < 1.0f)
		clipCoords.w = 1.f;

	Vector3 M;
	M.x = clipCoords.x / clipCoords.w;
	M.y = clipCoords.y / clipCoords.w;
	M.z = clipCoords.z / clipCoords.w;

	out.x = (screen.x / 2.f * M.x) + (M.x + screen.x / 2.f);
	out.y = -(screen.y / 2.f * M.y) + (M.y + screen.y / 2.f);


	return out;
}



GameRenderer renderer;