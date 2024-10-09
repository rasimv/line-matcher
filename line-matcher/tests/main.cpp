#include <core/LineMatcher.h>
#include "mocks.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::ByMove;
using ::testing::AnyOf;
using ::testing::AtLeast;
using stdfspath = std::filesystem::path;

TEST(LineMatch, Config1)
{
	std::regex pattern{"9.*j.*j", std::regex_constants::grep};
	DirWalkerMock dirWalker;
	FileReaderFactoryMock fileReaderFactory;
	OutputMock output;

	EXPECT_CALL(dirWalker, next())
						.WillOnce(Return(stdfspath{"/home/rv/1.txt"}))
						.WillOnce(Return(stdfspath{"/home/rv/extra/a.txt"}))
						.WillOnce(Return(stdfspath{"/home/rv/q1.txt"}))
						.WillRepeatedly(Return(stdfspath{}));
	EXPECT_CALL(dirWalker, root()).Times(AtLeast(1))
						.WillRepeatedly(Return(stdfspath{"/home/rv"}));

	std::unique_ptr<FileReaderMock> fileReader1{new FileReaderMock{}},
									fileReader2{new FileReaderMock{}},
									fileReader3{new FileReaderMock{}};

	EXPECT_CALL(*fileReader1, ok()).WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader1, filepath()).
							WillRepeatedly(Return(stdfspath{"/home/rv/1.txt"}));
	EXPECT_CALL(*fileReader1, getline())
								.WillOnce(Return(std::string{"gjw48jg98"}))
								.WillOnce(Return(std::string{"jgwgw0erijg"}))
								.WillOnce(Return(std::string{"g9o5jg9o4jg9o"}))
								.WillRepeatedly(Return(std::string{}));
	EXPECT_CALL(*fileReader1, eof())
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader2, ok()).WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader2, filepath()).
							WillRepeatedly(Return(stdfspath{"/home/rv/extra/a.txt"}));
	EXPECT_CALL(*fileReader2, getline())
								.WillOnce(Return(std::string{"eg98h984gh9"}))
								.WillOnce(Return(std::string{"sw9j48yjj84i"}))
								.WillOnce(Return(std::string{"faw84hf"}))
								.WillOnce(Return(std::string{"hfsw48hogo"}))
								.WillRepeatedly(Return(std::string{}));
	EXPECT_CALL(*fileReader2, eof())
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader3, ok()).WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader3, filepath()).
							WillRepeatedly(Return(stdfspath{"/home/rv/q1.txt"}));
	EXPECT_CALL(*fileReader3, getline())
								.WillOnce(Return(std::string{"sgr5hroireh"}))
								.WillOnce(Return(std::string{"s9dgj980jjk"}))
								.WillRepeatedly(Return(std::string{}));
	EXPECT_CALL(*fileReader3, eof())
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillRepeatedly(Return(true));

	EXPECT_CALL(fileReaderFactory, create(stdfspath{"/home/rv/1.txt"}))
						.WillOnce(::testing::Return(ByMove(std::move(fileReader1))));
	EXPECT_CALL(fileReaderFactory, create(stdfspath{"/home/rv/extra/a.txt"}))
						.WillOnce(::testing::Return(ByMove(std::move(fileReader2))));
	EXPECT_CALL(fileReaderFactory, create(stdfspath{"/home/rv/q1.txt"}))
						.WillOnce(::testing::Return(ByMove(std::move(fileReader3))));

	EXPECT_CALL(output, log(std::string{"1.txt:3:g9o5jg9o4jg9o"})).Times(1);
	EXPECT_CALL(output, log(std::string{"extra/a.txt:2:sw9j48yjj84i"})).Times(1);
	EXPECT_CALL(output, log(std::string{"q1.txt:2:s9dgj980jjk"})).Times(1);

	LineMatcher lm{pattern, &dirWalker, &fileReaderFactory, &output};

	lm.setForwardSlashes(true);

	lm.start();
	lm.wait();
}

TEST(LineMatch, Config2)
{
	std::regex pattern{"9.\\{4\\}9", std::regex_constants::grep};
	DirWalkerMock dirWalker;
	FileReaderFactoryMock fileReaderFactory;
	OutputMock output;

	EXPECT_CALL(dirWalker, next())
						.WillOnce(Return(stdfspath{"/home/rv/1.txt"}))
						.WillOnce(Return(stdfspath{"/home/rv/extra/a.txt"}))
						.WillOnce(Return(stdfspath{"/home/rv/q1.txt"}))
						.WillRepeatedly(Return(stdfspath{}));
	EXPECT_CALL(dirWalker, root()).Times(AtLeast(1))
						.WillRepeatedly(Return(stdfspath{"/home/rv"}));

	std::unique_ptr<FileReaderMock> fileReader1{new FileReaderMock{}},
									fileReader2{new FileReaderMock{}},
									fileReader3{new FileReaderMock{}};

	EXPECT_CALL(*fileReader1, ok()).WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader1, filepath()).
							WillRepeatedly(Return(stdfspath{"/home/rv/1.txt"}));
	EXPECT_CALL(*fileReader1, getline())
								.WillOnce(Return(std::string{"gjw48jg98"}))
								.WillOnce(Return(std::string{"jgwgw0erijg"}))
								.WillOnce(Return(std::string{"g9o5jg9o4jg9o"}))
								.WillRepeatedly(Return(std::string{}));
	EXPECT_CALL(*fileReader1, eof())
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader2, ok()).WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader2, filepath()).
							WillRepeatedly(Return(stdfspath{"/home/rv/extra/a.txt"}));
	EXPECT_CALL(*fileReader2, getline())
								.WillOnce(Return(std::string{"eg98h984gh9"}))
								.WillOnce(Return(std::string{"sw9j48yjj84i"}))
								.WillOnce(Return(std::string{"faw84hf"}))
								.WillOnce(Return(std::string{"hfsw48hogo"}))
								.WillRepeatedly(Return(std::string{}));
	EXPECT_CALL(*fileReader2, eof())
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader3, ok()).WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader3, filepath()).
							WillRepeatedly(Return(stdfspath{"/home/rv/q1.txt"}));
	EXPECT_CALL(*fileReader3, getline())
								.WillOnce(Return(std::string{"sgr5hroireh"}))
								.WillOnce(Return(std::string{"s9dgj980jjk"}))
								.WillRepeatedly(Return(std::string{}));
	EXPECT_CALL(*fileReader3, eof())
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillRepeatedly(Return(true));

	EXPECT_CALL(fileReaderFactory, create(stdfspath{"/home/rv/1.txt"}))
						.WillOnce(::testing::Return(ByMove(std::move(fileReader1))));
	EXPECT_CALL(fileReaderFactory, create(stdfspath{"/home/rv/extra/a.txt"}))
						.WillOnce(::testing::Return(ByMove(std::move(fileReader2))));
	EXPECT_CALL(fileReaderFactory, create(stdfspath{"/home/rv/q1.txt"}))
						.WillOnce(::testing::Return(ByMove(std::move(fileReader3))));

	EXPECT_CALL(output, log(std::string{"1.txt:3:g9o5jg9o4jg9o"})).Times(1);
	EXPECT_CALL(output, log(std::string{"extra/a.txt:1:eg98h984gh9"})).Times(1);

	LineMatcher lm{pattern, &dirWalker, &fileReaderFactory, &output};

	lm.setForwardSlashes(true);

	lm.start();
	lm.wait();
}

TEST(LineMatch, NothingFound)
{
	std::regex pattern{"f493h", std::regex_constants::grep};
	DirWalkerMock dirWalker;
	FileReaderFactoryMock fileReaderFactory;
	OutputMock output;

	EXPECT_CALL(dirWalker, next())
						.WillOnce(Return(stdfspath{"/home/rv/1.txt"}))
						.WillOnce(Return(stdfspath{"/home/rv/extra/a.txt"}))
						.WillOnce(Return(stdfspath{"/home/rv/q1.txt"}))
						.WillRepeatedly(Return(stdfspath{}));
	EXPECT_CALL(dirWalker, root()).Times(0);

	std::unique_ptr<FileReaderMock> fileReader1{new FileReaderMock{}},
									fileReader2{new FileReaderMock{}},
									fileReader3{new FileReaderMock{}};

	EXPECT_CALL(*fileReader1, ok()).WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader1, filepath()).
							WillRepeatedly(Return(stdfspath{"/home/rv/1.txt"}));
	EXPECT_CALL(*fileReader1, getline())
								.WillOnce(Return(std::string{"gjw48jg98"}))
								.WillOnce(Return(std::string{"jgwgw0erijg"}))
								.WillOnce(Return(std::string{"g9o5jg9o4jg9o"}))
								.WillRepeatedly(Return(std::string{}));
	EXPECT_CALL(*fileReader1, eof())
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader2, ok()).WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader2, filepath()).
							WillRepeatedly(Return(stdfspath{"/home/rv/extra/a.txt"}));
	EXPECT_CALL(*fileReader2, getline())
								.WillOnce(Return(std::string{"eg98h984gh9"}))
								.WillOnce(Return(std::string{"sw9j48yjj84i"}))
								.WillOnce(Return(std::string{"faw84hf"}))
								.WillOnce(Return(std::string{"hfsw48hogo"}))
								.WillRepeatedly(Return(std::string{}));
	EXPECT_CALL(*fileReader2, eof())
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader3, ok()).WillRepeatedly(Return(true));
	EXPECT_CALL(*fileReader3, filepath()).
							WillRepeatedly(Return(stdfspath{"/home/rv/q1.txt"}));
	EXPECT_CALL(*fileReader3, getline())
								.WillOnce(Return(std::string{"sgr5hroireh"}))
								.WillOnce(Return(std::string{"s9dgj980jjk"}))
								.WillRepeatedly(Return(std::string{}));
	EXPECT_CALL(*fileReader3, eof())
								.WillOnce(Return(false))
								.WillOnce(Return(false))
								.WillRepeatedly(Return(true));

	EXPECT_CALL(fileReaderFactory, create(stdfspath{"/home/rv/1.txt"}))
						.WillOnce(::testing::Return(ByMove(std::move(fileReader1))));
	EXPECT_CALL(fileReaderFactory, create(stdfspath{"/home/rv/extra/a.txt"}))
						.WillOnce(::testing::Return(ByMove(std::move(fileReader2))));
	EXPECT_CALL(fileReaderFactory, create(stdfspath{"/home/rv/q1.txt"}))
						.WillOnce(::testing::Return(ByMove(std::move(fileReader3))));

	EXPECT_CALL(output, log(testing::An<const std::string &>())).Times(0);

	LineMatcher lm{pattern, &dirWalker, &fileReaderFactory, &output};

	lm.setForwardSlashes(true);

	lm.start();
	lm.wait();
}

TEST(LineMatch, NoFiles)
{
	std::regex pattern{"hfq3h29", std::regex_constants::grep};
	DirWalkerMock dirWalker;
	FileReaderFactoryMock fileReaderFactory;
	OutputMock output;

	EXPECT_CALL(dirWalker, next()).WillRepeatedly(Return(stdfspath{}));
	EXPECT_CALL(dirWalker, root()).Times(0);

	EXPECT_CALL(fileReaderFactory, create(_)).Times(0);

	EXPECT_CALL(output, log(testing::An<const std::string &>())).Times(0);

	LineMatcher lm{pattern, &dirWalker, &fileReaderFactory, &output};

	lm.setForwardSlashes(true);

	lm.start();
	lm.wait();
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
