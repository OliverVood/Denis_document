<?php

	namespace Proj\Admin\Editor;

	use JetBrains\PhpStorm\NoReturn;

	use Base\Editor\EditorMySQLi;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;

	class News extends EditorMySQLi {

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);
		}

		protected function Where(array $params): array {
			return [
				'`state` != ' . Consts\News::STATES['delete']
			];
		}

		protected function Order(): array {
			return [
				'`datecr` DESC',
				'`id` ASC'
			];
		}

		protected function RegTitles(): void {
			$this->titleSelect = 'Список новостей';
			$this->titleCreate = 'Добавить новость';
			$this->titleUpdate = 'Редактирование новости';
			$this->titleDelete = 'Удалить новость?';

			$this->titleDoCreate = 'Новость добавлена';
			$this->titleDoUpdate = 'Новость изменена';
			$this->titleDoDelete = 'Новость удалена';
		}

		protected function FieldsSelect(array $params): array {
			return [
				'id' => '#',
				'state' => 'Состояние',
				'datepb' => 'Дата публикации',
				'header' => 'Заголовок'
			];
		}

		protected function FieldsCreate(array $params): array {
			return [
				'state' => ['skin' => 'hidden', 'name' => 'Состояние', 'default' => Consts\News::STATES['draft']],
				'header' => ['skin' => 'text', 'name' => 'Заголовок', 'default' => ''],
				'content' => ['skin' => 'textarea', 'name' => 'Текст', 'default' => ''],
				'cover' => ['skin' => 'file', 'name' => 'Обложка', 'default' => 'Выберите обложку', 'params' => ['accept' => '.jpg, .jpeg, .png']],
				'datepb' => ['skin' => 'datetime', 'name' => 'Дата публикации']
			];
		}

		protected function FieldsUpdate(array $params): array {
			return [
				'state' => ['skin' => 'select', 'name' => 'Состояние'],
				'header' => ['skin' => 'text', 'name' => 'Заголовок'],
				'content' => ['skin' => 'textarea', 'name' => 'Текст'],
				'cover' => ['skin' => 'file', 'name' => 'Обложка', 'params' => ['accept' => '.jpg, .jpeg, .png']],
				'datepb' => ['skin' => 'datetime', 'name' => 'Дата публикации']
			];
		}

		public function PrepareOnUpdate(int $id, array & $item, array &$data): void {
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
				[$hash, $ext] = $this->SaveFile($id);
				$this->table->Update(['hash' => $hash, 'ext' => $ext], "`id` = {$id}");
			}

			SendJSONSuccess(['message' => $this->titleDoCreate, 'html' => $this->Select()]);
		}

		#[NoReturn] public function DoUpdate(): void {
			$id = (int)GetParam('id', 0);
			$data = GetParam('form', []);

			if ($_FILES['form']['tmp_name']['cover']) {
				$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");
				if ($old_file) unlink(Consts\News::PATH_COVER . $old_file);

				[$data['hash'], $data['ext']] = $this->SaveFile($id);
			}

			$this->table->Update($data, "`id` = {$id}");

			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
		}

		private function SaveFile(int $id): array {
			$temp_path = $_FILES['form']['tmp_name']['cover'];
			$temp_name = $_FILES['form']['name']['cover'];
			$dir = Consts\News::PATH_COVER;
			$hash = hash_file('md5', $temp_path);
			$info = pathinfo($temp_name);
			$ext = $info['extension'];
			$name = "{$hash}.{$id}.{$ext}";

			if (!is_dir($dir)) mkdir($dir, 0777, true);
			move_uploaded_file($temp_path, $dir . $name);

			return [$hash, $ext];
		}

	}