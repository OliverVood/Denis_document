<?php

	namespace Proj\Admin\Editor\Model;

	use Base\DB\MySQLi\Table;
	use Base\DB\MySQLi\Select;
	use Base\Editor\MySQLi\Model;
	use Proj\Units\Consts;

	class Change extends Model {
		public function __construct(Table $table, array $params = []) {
			parent::__construct($table, $params);
		}

		protected function Init(): void {
			$this->querySelect = new Select();
			$this->querySelect
				->calc('*')
				->table($this->table->GetName())
				->where('`state` != ' . Consts\Changes::STATE_DELETE)
				->where("`cid` = {$this->params['cid']}")
				->order('datecr', 'DESC')
				->order('id');
		}

		public function Create(array $data, array $params = []): bool {
			$id = $this->table->Insert($data);

			if ($_FILES['form']['tmp_name']['cover']) {
				[$hash, $ext] = $this->SaveCover($id);
				$this->table->Update(['hash' => $hash, 'ext' => $ext], "`id` = {$id}");
			}

			return true;
		}

		public function Update(array $data, int $id): bool {
			if ($_FILES['form']['tmp_name']['cover']) {
				$this->DeleteCover($id);
				[$data['hash'], $data['ext']] = $this->SaveCover($id);
			}

			$this->table->Update($data, "`id` = {$id}");

			return true;
		}

		public function SaveCover(int $id): array {
			$temp_path = $_FILES['form']['tmp_name']['cover'];
			$temp_name = $_FILES['form']['name']['cover'];
			$dir = Consts\Changes::PATH_COVER;
			$hash = hash_file('md5', $temp_path);
			$info = pathinfo($temp_name);
			$ext = $info['extension'];
			$name = "{$hash}.{$id}.{$ext}";

			if (!is_dir($dir)) mkdir($dir, 0777, true);
			move_uploaded_file($temp_path, $dir . $name);

			return [$hash, $ext];
		}

		public function DeleteCover($id): void {
			$old_file = $this->table->SelectOneFieldCalc("CONCAT(`hash`, '.', `id`, '.', `ext`) AS `name`", 'name', "`id` = {$id}");
			if ($old_file) unlink(Consts\Changes::PATH_COVER . $old_file);
		}

	}