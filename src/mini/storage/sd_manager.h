#pragma once

#include <Arduino.h>

#include <FS.h>
#include <SD.h>

namespace SDManager
{
    bool begin();

    // Cleanly unmounts the SD card. Call this before any intentional
    // reboot, OTA update, or low-battery shutdown so the card is never
    // left in a state that only ever gets closed by a power cut.
    bool end();

    bool mounted();

    bool exists(const char* path);

    bool mkdir(const char* path);

    bool remove(const char* path);

    bool initializeFilesystem();

    String readFile(const char* path);

    // Atomic: writes to a temp file, then renames into place only on
    // success. A power loss mid-write leaves an orphaned .tmp file,
    // never a half-written/corrupted real file.
    bool writeFile(const char* path, const String& data);

    // NOTE: appends are inherently incremental and can't be made fully
    // atomic the same way — flushed after every call to shrink the
    // exposure window, but repeated small appends are still riskier
    // than batched writes. Keep append call sites low-frequency.
    bool appendFile(const char* path, const String& data);

    // Opens path + ".tmp" for writing and returns it, along with the
    // temp path the caller must pass to commitAtomicWrite() once the
    // write is confirmed complete. Use this instead of openForWrite()
    // for any write you can't do in one shot (e.g. streamed downloads).
    File openForWriteAtomic(const char* path, String& outTempPath);

    // Finalizes an atomic write: removes any existing file at
    // finalPath, then renames tempPath into place. Only call this
    // after verifying the temp file's contents are complete and correct.
    bool commitAtomicWrite(const char* finalPath, const String& tempPath);

    // Direct, non-atomic write handle. Prefer writeFile() or
    // openForWriteAtomic() — this is kept for call sites that manage
    // their own atomicity.
    File openForWrite(const char* path);
}
