<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\MySQLi\Table;
	use Base\DB\Select;
	use Base\EditorMySQLi\Model;
	use Proj\Units\Consts;

	class News extends Model {
		public function __construct(Table $table, array $params = []) {
			parent::__construct($table, $params);
		}

		protected function Init(): void {
			$this->querySelect = new Select();
			$this->querySelect
				->calc('*')
				->table($this->table->GetName())
				->where('`state` != '. Consts\News::STATE_DELETE)
				->order('datecr', 'DESC')
				->order('id', 'DESC');
		}

		public function Create(array $data): void {
			$id = $this->table->Insert($data);

			if ($_FILES['form']['tmp_name']['cover']) {
				[$hash, $ext] = $this->SaveCover($id);
				$this->table->Update(['hash' => $hash, 'ext' => $ext], "`id` = {$id}");
			}
		}

		public function Update(array $data, int $id): void {
			if ($_FILES['form']['tmp_name']['cover']) {
				$this->DeleteCover($id);
				[$data['hash'], $data['ext']] = $this->SaveCover($id);
			}

			$this->table->Update($data, "`id` = {$id}");
		}

		private function SaveCover(int $id): array {
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

		private function DeleteCover($id): void {
			$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");
			if ($old_file) unlink(Consts\News::PATH_COVER . $old_file);
		}

	}