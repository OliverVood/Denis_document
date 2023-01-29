<?php

	namespace Proj\Admin\Editor;

	use JetBrains\PhpStorm\NoReturn;

	use Base\Editor\EditorMySQLi;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;

	class News extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			$params = [
				'order' => [
					'`datecr` DESC',
					'`id` ASC'
				],
				'select' => [
					'id' => '#',
					'state' => 'Состояние',
					'datecr' => 'Дата создания',
					'header' => 'Заголовок'
				],
				'create' => [
					'state' => ['skin' => 'hidden', 'name' => 'Состояние', 'default' => Consts\News::STATES['draft']],
					'header' => ['skin' => 'text', 'name' => 'Заголовок', 'default' => ''],
					'content' => ['skin' => 'textarea', 'name' => 'Текст', 'default' => ''],
					'cover' => ['skin' => 'file', 'name' => 'Обложка', 'default' => 'Выберите обложку', 'params' => ['accept' => '.jpg, .jpeg, .png']]
				],
				'update' => [
					'state' => ['skin' => 'select', 'name' => 'Состояние'],
					'header' => ['skin' => 'text', 'name' => 'Заголовок'],
					'content' => ['skin' => 'textarea', 'name' => 'Текст'],
					'cover' => ['skin' => 'file', 'name' => 'Обложка', 'params' => ['accept' => '.jpg, .jpeg, .png']]
				]
			];

			parent::__construct($name, $table, $params);

			$this->titleSelect = 'Список новостей';
			$this->titleCreate = 'Добавить новость';
			$this->titleUpdate = 'Редактирование новости';

			$this->titleDoCreate = 'Новость добавлена';
			$this->titleDoUpdate = 'Новость изменена';
		}

		public function PrepareOnUpdate(int $id, array &$item, array &$data) : void {
			$data['state'] = [
				Consts\News::STATE_DRAFT	=> 'Черновик',
				Consts\News::STATE_ACTIVE	=> 'Активная',
				Consts\News::STATE_INACTIVE	=> 'Не активная',
			];
		}

		#[NoReturn] public function DoCreate(): void {
			$data = GetParam('form', []);

			$id = $this->table->Insert($data);

			if ($_FILES['form']['tmp_name']['cover']) {
				$file_name = $this->SaveFile($_FILES['form'], 'cover', $id);
				$this->table->Update(['cover' => $file_name], "`id` = {$id}");
			}

			SendJSONSuccess(['message' => $this->titleDoCreate, 'html' => $this->Select()]);
		}

		#[NoReturn] public function DoUpdate(): void {
			$id = (int)GetParam('id', 0);
			$data = GetParam('form', []);

			if ($_FILES['form']['tmp_name']['cover']) {
				$old_file = $this->table->SelectOneField('cover', "`id` = {$id}");
				if ($old_file) unlink(Consts\News::PATH_COVER . $old_file);

				$file_name = $this->SaveFile($_FILES['form'], 'cover', $id);
				$data['cover'] = $file_name;
			}

			$this->table->Update($data, "`id` = {$id}");

			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
		}

		private function SaveFile(array $file, string $name_param, string $prefix = ''): string {
			$temp_path = $file['tmp_name'][$name_param];
			$temp_name = $file['name'][$name_param];
			$info = pathinfo($temp_name);

			$name = uniqid("{$prefix}.");
			$ext = $info['extension'];
			$file_name = "{$name}.{$ext}";

			if (!is_dir(Consts\News::PATH_COVER)) mkdir(Consts\News::PATH_COVER, 0777, true);
			move_uploaded_file($temp_path, Consts\News::PATH_COVER . $file_name);

			return $file_name;
		}

	}