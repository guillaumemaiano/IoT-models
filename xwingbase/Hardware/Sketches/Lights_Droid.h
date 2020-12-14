// helper methods
#ifdef __cplusplus
extern "C" {
#endif

void setupDroidLights(struct DroidLightsParameters*);
void setDroidLightStatus(int, struct DroidLightsParameters*);

#ifdef __cplusplus
}
#endif
static const int defaultDuration = 270; // ceil(4 seconds /15 points)
static const int maxDuration = 4000; // max duration of a cycle in milliseconds
static const int separationInterval = 100; // a millisecond duration to separate "points" visually
static const int maxPoints = 15; // max occurrences of a "point" (up signal of varying length)
static const int durations[3] = {100, 300, 500}; // possible durations of a point (short, medium, long)
