$version = "1.3"
$sourceDir = "src"
$destinationDir = ".release\Flipper-$version"
$zipFile = ".release\Flipper-$version.zip"

New-Item -ItemType Directory -Force -Path $destinationDir | Out-Null

Get-ChildItem -Path $sourceDir -Recurse -Exclude ".*" | ForEach-Object {
    $destinationPath = $_.FullName.Replace($sourceDir, $destinationDir)
    Copy-Item -Path $_.FullName -Destination $destinationPath -Force
}

$renameFile = Join-Path -Path $destinationDir -ChildPath "main.cpp"
$renamedFile = Join-Path -Path $destinationDir -ChildPath "Flipper-$version.ino"
Move-Item -Path $renameFile -Destination $renamedFile -Force

Compress-Archive -Path $destinationDir -DestinationPath $zipFile -Force
Remove-Item -Path $destinationDir -Recurse -Force