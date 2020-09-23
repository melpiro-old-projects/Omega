#include "LinuxFunctions.h"
namespace sys
{
    std::string read_from_clipboard()
    {
        const unsigned buffsize = 2048;
        char buffer[buffsize];
        std::string result;
        std::shared_ptr<FILE> pipe(popen("xclip -selection clipboard -o", "r"), pclose);

        if (!pipe)
            throw std::runtime_error("read_from_clipboard: popen() failed!");

        while (!feof(pipe.get()))
        {
            if (fgets(buffer, buffsize, pipe.get()) != NULL)
                result += buffer;
        }
        return result;
    }

    void write_to_clipboard ( std::string tekst)
    {
        std::shared_ptr<FILE> pipe(popen("xclip -selection clipboard -i", "w"), pclose);

        if (!pipe)
            throw std::runtime_error("write_to_clipboard: popen() failed!");

        fprintf(pipe.get(), "%s", tekst.c_str());

        if (ferror (pipe.get()))
            throw std::runtime_error("write_to_clipboard: Output to stream failed.");
    }

}