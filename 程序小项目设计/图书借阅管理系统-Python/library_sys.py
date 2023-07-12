import json
from datetime import date


# 读取文件并转换为列表
def read_file_to_list(file_path):
    try:
        with open(file_path, 'r') as file:
            data = json.load(file)
            return data
    except Exception:
        return []


# 写入列表到文件
def write_list_to_file(data, file_path):
    with open(file_path, 'w') as file:
        json.dump(data, file)


# 注册用户
def register_user(user_list, privilege: int = 1):
    # 将用户信息保存到文件或数据库中
    newUser = {}
    idExists = False
    newUser['id'] = input(">> 请输入用户ID: ")
    for user in user_list:
        if user['id'] == newUser['id']:
            idExists = True
            break
    if idExists:
        print("# ID重复, 请确保唯一")
        input("请按任意键继续")
        return

    newUser['name'] = input(">> 请输入用户名: ")
    newUser['password'] = input(">> 请输入密码: ")
    newUser['privilege'] = privilege
    newUser['borrow'] = []

    user_list.append(newUser)
    input(f"# 添加新用户({newUser['name']})成功")


# 用户登录
def login(user_list, current_user):
    username = input(">> 请输入用户名: ")
    # 验证用户名和密码的正确性
    for i, user in enumerate(user_list):
        if user['name'] == username:
            if user['password'] == input(">> 请输入密码: "):
                current_user['name'] = user['name']
                current_user['id'] = user['id']
                current_user['privilege'] = user['privilege']
                current_user['index'] = i
                return True
            else:
                print("# 密码错误")
                return False

    print("# 用户不存在")
    return False


# 添加图书
def add_book(book_list):
    print("\n添加图书")
    print("==========" * 9)
    # 暂不添加编号唯一验证
    book = {}
    idExists = False
    book['id'] = input(">> 请输入图书编号: ")
    for book2 in book_list:
        if book2['id'] == book['id']:
            idExists = True
            break
    if idExists:
        print("# 图书编号重复, 请确保唯一")
        input("请按任意键继续")
        return book

    book['name'] = input(">> 请输入图书名称: ")
    book['author'] = input(">> 请输入图书作者: ")
    book['price'] = float(input(">> 请输入图书价格: "))
    book['inventory'] = int(input(">> 请输入库存: "))
    book['lend'] = 0
    book_list.append(book)

    print("# 图书添加成功。")
    input("请按任意键继续")


# 修改图书
def update_book(book_list):
    print("\n图书修改")
    print("==========" * 9)
    book_id = input(">> 请输入要修改的图书编号(0退出): ")
    if book_id == '0':
        return
    found = False

    for book in book_list:
        if book['id'] == book_id:
            print("# 已找到图书:")
            print("%-10s%-20s%-20s%-10s%-10s%s" % ("编号", "名称", "作者", "价格", "库存", "借出"))
            print("%-10s%-20s%-20s%-10s%-10s%s" % (book['id'], book['name'], book['author'],
                                                   book['price'], book['inventory'], book['lend']))
            book['name'] = input(">> 请输入修改后的图书名称: ")
            book['author'] = input(">> 请输入修改后的图书作者: ")
            book['price'] = float(input(">> 请输入修改后的图书价格: "))
            book['inventory'] = int(input(">> 请输入修改后的库存: "))
            found = True
            break

    if found:
        write_list_to_file(book_list, 'books.json')
        print("# 图书信息修改成功。")
    else:
        print("# 未找到该图书编号。")
    input("请按任意键继续")


# 删除图书
def delete_book(book_list):
    print("\n图书删除")
    print("==========" * 9)
    book_id = input(">> 请输入要删除的图书编号(0退出): ")
    if book_id == '0':
        return
    found = False

    for book in book_list:
        if book['id'] == book_id:
            book_list.remove(book)
            found = True
            break

    if found:
        write_list_to_file(book_list, 'books.json')
        print("# 图书删除成功。")
    else:
        print("# 未找到该图书编号。")
    input("请按任意键继续")


# 查询图书
def search_book(book_list):
    print("\n图书查询")
    print("==========" * 9)
    book_name = input(">> 请输入要查询的图书名称: ")
    found = False

    for book in book_list:
        if book['name'] == book_name:
            print("# 找到图书信息:")
            print("----------" * 9)
            print("%-10s%-20s%-20s%-10s%-10s%s" % ("编号", "名称", "作者", "价格", "库存", "借出"))
            print("----------" * 9)
            print("%-10s%-20s%-20s%-10s%-10s%s" % (book['id'], book['name'], book['author'],
                                                   book['price'], book['inventory'], book['lend']))
            found = True

    if not found:
        print("# 未找到该图书名称的图书。")
    input("请按任意键继续")


# 借阅图书
def borrow_book(current_user, book_list, user_list, borrow_list):
    print("\n图书借阅")
    print("==========" * 9)
    book_name = input(">> 请输入要借阅的图书名: ")

    # 检查图书是否存在且可借阅
    book_exists = False
    borrowed_book = {}
    for book in book_list:
        # 存在 且有 库存
        if book['name'] == book_name and book['inventory'] != 0:
            book_exists = True
            borrowed_book = book

    if book_exists:
        borrow_date = str(date.today())

        user = user_list[current_user['index']]
        if len(user['borrow']) == 5:
            print("# 超过最大借阅数量！ 请归还部分图书再借阅")
            input("请按任意键继续")
            return
        
        for book in user['borrow']:
            if book['book_id'] == borrowed_book['id']:
                print("# 请勿重复借阅")
                input("请按任意键继续")
                return

        # 添加自己借阅记录
        user['borrow'].append({
            'book_id': borrowed_book['id'],
            'book_name': book_name,
            'borrow_date': borrow_date
        })

        # 更新图书的信息
        for book in book_list:
            if book['id'] == borrowed_book['id']:
                book['inventory'] = book['inventory'] - 1
                book['lend'] = book['lend'] + 1
                break

        # 添加全局借阅记录
        borrow_list.append({
            'book_name': book_name,
            'user_name': current_user['name'],
            'borrow_date': borrow_date
        })

        print("# 借阅成功。")
    else:
        print("# 图书不存在或已借阅完。")
    input("请按任意键继续")


# 归还图书
def return_book(current_user, book_list, user_list, borrow_list):
    print("\n图书归还")
    print("==========" * 9)
    book_name = input(">> 请输入要归还的图书名称: ")
    # 检查借阅记录是否存在
    record_found = False
    for record in borrow_list:
        if record['book_name'] == book_name and record['user_name'] == current_user['name']:
            record_found = True
            break

    if record_found:
        # 更新自己图书的借阅信息
        for user in user_list:
            if user['id'] == current_user['id']:
                for book in user['borrow']:
                    if book['book_name'] == book_name:
                        user['borrow'].remove(book)
                        break
                break

        # 清除借阅记录
        for record in borrow_list:
            if record['book_name'] == book_name and record['user_name'] == current_user['name']:
                borrow_list.remove(record)
                break

        # 更新图书的信息
        for book in book_list:
            if book['name'] == book_name:
                book['inventory'] = book['inventory'] + 1
                book['lend'] = book['lend'] - 1
                break

        print("# 归还成功。")
    else:
        print("# 未找到相关的借阅记录。")


# 显示所有图书
def display_all_books(book_list):
    if len(book_list) == 0:
        print("\n# 图书库存为空。")
    else:
        print("\n图书库存信息:")
        print("----------" * 9)
        print("%-10s%-20s%-20s%-10s%-10s%s" % ("编号", "名称", "作者", "价格", "库存", "借出"))
        print("----------" * 9)
        for book in book_list:
            print("%-10s%-20s%-20s%-10s%-10s%s" % (book['id'], book['name'], book['author'],
                                                   book['price'], book['inventory'], book['lend']))
            print("----------" * 9)
    input("请按任意键继续")


def show_borrow_list_admin(borrow_list):
    print("\n图书借阅记录:")
    print("----------" * 9)
    print("%-10s%-10s%-10s" % ("用户", "书籍", "日期"))
    print("----------" * 9)
    for book in borrow_list:
        print("%-10s%-10s%-10s" % (book['user_name'], book['book_name'], book['borrow_date']))
        print("----------" * 9)
    input("请按任意键继续")


def show_borrow_list_user(current_user, borrow_list):
    print("\n图书借阅记录:")
    print("----------" * 9)
    print("%-10s%-10s%-10s" % ("用户", "书籍", "日期"))
    print("----------" * 9)
    for book in borrow_list:
        if book['user_name'] == current_user['name']:
            print("%-10s%-10s%-10s" % (book['user_name'], book['book_name'], book['borrow_date']))
            print("----------" * 9)
    input("请按任意键继续")


def reset_user_password(user_list):
    print("\n重置用户密码")
    print("==========" * 9)
    user_name = input(">> 请输入要重置密码的用户名: ")
    for user in user_list:
        if user['name'] == user_name:
            user['password'] = '123456'
            print("# 已重置初始密码: 123456")
            input("请按任意键继续")
            return
    print("# 未找到用户")
    input("请按任意键继续")


def edit_user(current_user, user_list):
    print("\n用户管理")
    print("==========" * 9)
    print("\t1. 用户列表")
    print("\t2. 添加管理员")
    print("\t3. 重置用户密码")
    print("\t4. 修改当前密码")
    print("\t5. 删除用户")
    print("\t0. 返回")
    choice = input(">> 请选择: ")
    if choice == '1':
        print("%-10s%-10s%-10s%s" % ('用户ID', '用户名', '权限', '借阅数'))
        for user in user_list:
            print("%-10s%-10s%-10s%s" % (user['id'], user['name'], user['privilege'], len(user['borrow'])))
        input("请按任意键继续")
    elif choice == '2':
        register_user(user_list, 0)
    elif choice == '3':
        reset_user_password(user_list)
    elif choice == '4':
        change_password(current_user['index'], user_list)
    elif choice == '5':
        delete_user = input(">> 请输入删除的用户ID: ")
        # 暂不实现图书归还处理
        for user in user_list:
            if user['id'] == delete_user:
                user_list.remove(user)
                print("# 删除成功")
                input("请按任意键继续")
                return
        print("# 用户不存在")
        input("请按任意键继续")


def change_password(index, user_list):
    new_password = input(">> 请输入新密码: ")
    new_password2 = input(">> 请再次确认: ")
    if new_password == new_password2:
        user_list[index]['password'] = new_password
        print("# 修改成功")
    else:
        print("# 两次输入不一致")
    input("请按任意键继续")


# 主菜单
def show_menu_admin(current_user, book_list, user_list, borrow_list):
    while True:
        print("\n图书管理系统-管理员")
        print("==========" * 9)
        print("\t1. 添加图书")
        print("\t2. 修改图书")
        print("\t3. 删除图书")
        print("\t4. 查询图书")
        print("\t5. 借阅记录")
        print("\t6. 所有图书")
        print("\t7. 用户管理")
        print("\t0. 退出")
        choice = input(">> 请选择: ")

        if choice == '1':
            add_book(book_list)
        elif choice == '2':
            update_book(book_list)
        elif choice == '3':
            delete_book(book_list)
        elif choice == '4':
            search_book(book_list)
        elif choice == '5':
            show_borrow_list_admin(borrow_list)
        elif choice == '6':
            display_all_books(book_list)
        elif choice == '7':
            edit_user(current_user, user_list)
        else:
            write_list_to_file(book_list, 'books.json')
            write_list_to_file(user_list, 'users.json')
            write_list_to_file(borrow_list, 'borrows.json')
            return


def show_menu_user(current_user, book_list, user_list, borrow_list):
    while True:
        print("\n图书管理系统-借阅用户")
        print("==========" * 9)
        print("\t1. 查询图书")
        print("\t2. 借阅图书")
        print("\t3. 归还图书")
        print("\t4. 所有图书")
        print("\t5. 借阅记录")
        print("\t6. 修改密码")
        print("\t0. 退出登录")
        choice = input(">> 请选择: ")
        if choice == '1':
            search_book(book_list)
        elif choice == '2':
            borrow_book(current_user, book_list, user_list, borrow_list)
        elif choice == '3':
            return_book(current_user, book_list, user_list, borrow_list)
        elif choice == '4':
            display_all_books(book_list)
        elif choice == '5':
            show_borrow_list_user(current_user, borrow_list)
        elif choice == '6':
            change_password(current_user['index'], user_list)
        else:
            write_list_to_file(book_list, 'books.json')
            write_list_to_file(user_list, 'users.json')
            write_list_to_file(borrow_list, 'borrows.json')
            return


def main():
    book_list = read_file_to_list("books.json")
    user_list = read_file_to_list("users.json")
    borrow_list = read_file_to_list("borrows.json")
    current_user = {
        'name': '',
        'id': '',
        'privilege': 2,
        'index': 0
    }
    while True:
        print("# 欢迎进入图书管理系统 !!")
        print("==========" * 9)
        print("\t1. 登录")
        print("\t2. 注册")
        print("\t0. 退出")
        choice = input(">> 请选择: ")
        if choice == '1':
            is_login = login(user_list, current_user)
            if is_login and current_user['privilege'] == 0:
                show_menu_admin(current_user, book_list, user_list, borrow_list)
            elif is_login and current_user['privilege'] == 1:
                show_menu_user(current_user, book_list, user_list, borrow_list)

        elif choice == '2':
            register_user(user_list)

        else:
            write_list_to_file(book_list, 'books.json')
            write_list_to_file(user_list, 'users.json')
            write_list_to_file(borrow_list, 'borrows.json')
            exit()


if __name__ == '__main__':
    main()
    