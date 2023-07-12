// Copyright Epic Games, Inc. All Rights Reserved.

#include "DebuggingPlugin.h"

#define LOCTEXT_NAMESPACE "FDebuggingPluginModule"

void FDebuggingPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FDebuggingPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDebuggingPluginModule, DebuggingPlugin)