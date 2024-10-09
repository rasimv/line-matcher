#pragma once

#include <core/IDirWalker.h>
#include <core/IFileReaderFactory.h>
#include <core/IOutput.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class DirWalkerMock: public IDirWalker
{
public:
	MOCK_METHOD(std::filesystem::path, root, (), (const override));
	MOCK_METHOD(std::filesystem::path, next, (), (override));
};

class FileReaderMock: public IFileReader
{
public:
	MOCK_METHOD(bool, ok, (), (const override));
	MOCK_METHOD(std::filesystem::path, filepath, (), (const override));
	MOCK_METHOD(std::string, getline, (), (override));
	MOCK_METHOD(bool, eof, (), (const override));
};

class FileReaderFactoryMock: public IFileReaderFactory
{
public:
	MOCK_METHOD(IFileReaderUPtr, create, (const std::filesystem::path &filepath), (override));
};

class OutputMock: public IOutput
{
public:
	MOCK_METHOD(void, log, (const std::string &line), (override));
	MOCK_METHOD(void, log, (const std::wstring &line), (override));
};
