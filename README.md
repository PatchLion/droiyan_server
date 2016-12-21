##For vc6  ---> vs2013
###VS2013多字节工程问题

	使用VS2013编译旧版VC++程序时，提示Building an MFC project for a non-Unicode character set is deprecated，微软提供了解决方案。


###一、错误信息
    ------ 已启动全部重新生成:  项目: Server, 配置: Release Win32 ------  
    1>C:\Program Files (x86)\MSBuild\Microsoft.Cpp\v4.0\V120\Microsoft.CppBuild.targets(369,5): error MSB8031: Building an MFC project for a non-Unicode character set is deprecated. You must change the project property to Unicode or download an additional library. See http://go.microsoft.com/fwlink/p/?LinkId=286820 for more information.  
    ========== 全部重新生成:  成功 0 个，失败 1 个，跳过 0 个 ==========  
 


###二、微软解释

      用于多字节字符编码 (MBCS) 的 MFC 库 (DLL) 不再包含于 Visual Studio 中，但是可用作插件，您可以在任何装有 Visual Studio Professional、Visual Studio Premium 或 Visual Studio Ultimate 的计算机上下载和安装。（在 Visual Studio 中，必须启用 MFC。）安装需要大约 440 MB 磁盘空间，包括英语（美国）和 DLL 的本地化版本。

在安装 MBCS DLL 后，如果卸载或修复 Visual Studio，则还会卸载或修复。 但是，如果只禁用 MFC，MBCS DLL 仍会保留在系统上。 如果仅卸载或修复 MBCS DLL，将不会修改 Visual Studio。
	    

######详细信息： http://blogs.msdn.com/b/vcblog/archive/2013/07/08/mfc-support-for-mbcs-deprecated-in-visual-studio-2013.aspx

######下载地址： http://www.microsoft.com/zh-cn/download/details.aspx?id=40770