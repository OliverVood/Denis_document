<?php

	namespace Proj\Admin\Model;

	use Base\Model;
	use Base\Instance;
	use Proj\Units\Consts;

	class Composition extends Model {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);
		}

		public function CreateUnit(array $data): void {
			$sampleConsts = file_get_contents(__DIR__ . '/samples/consts.sample');

			$unitName = strtolower($data['name']);
			$unitDir = DIR_UNITS . $unitName . '/';

			$replace = [];
			$replace['<sample>'] = $unitName;
			$replace['<Sample>'] = ucfirst(strtolower($data['name']));
			$replace['<SAMPLE>'] = strtoupper($data['name']);

			$constsInstance = str_replace(array_keys($replace), $replace, $sampleConsts);
			$this->WriteFile($unitDir, "{$unitName}.consts.inc", $constsInstance);

			foreach ($data['routes'] as $route => ['entries' => $entries, 'binds' => $binds]) {
				$routeDir = $unitDir . $route . '/';

				$replace['[route]'] = strtolower($route);
				$replace['[Route]'] = ucfirst(strtolower($route));

				$prepareController = [
					'[MODEL_REQUIRE]'				=> '',
					'[MODEL_USE]'					=> '',
					'[MODEL_PROPERTY]'				=> '',
					'[MODEL_INSTANCE]'				=> '',
					'[CONTROLLER_XET_REQUIRE]'		=> '',
					'[CONTROLLER_USE]'				=> 'Base\Units',
					'[CONTROLLER_EXTENDS]'			=> 'Units',
					'[CONTROLLER_PARAM_ID]'			=> 'self::ID, ',
					'[CONTROLLER_PARAM_NAME]'		=> 'self::NAME, '
				];
				if ($binds & Consts\Composition::FILE_ACTIONS) {
					$prepareController['[CONTROLLER_XET_REQUIRE]']		= "\n\n\trequire DIR_UNITS . '<sample>/[route]/<sample>.actions.inc';";
					$prepareController['[CONTROLLER_USE]']				= 'Proj\[Route]\Actions';
					$prepareController['[CONTROLLER_EXTENDS]']			= 'Actions\<Sample>';
					$prepareController['[CONTROLLER_PARAM_ID]']			= '';
					$prepareController['[CONTROLLER_PARAM_NAME]']		= '';

					$sampleActions = file_get_contents(__DIR__ . '/samples/actions.sample');
					$sampleActions = str_replace(array_keys($replace), $replace, $sampleActions);
					$this->WriteFile($routeDir, "{$unitName}.actions.inc", $sampleActions);
				}
				if ($binds & Consts\Composition::FILE_STRUCTURE) {
					$prepareController['[CONTROLLER_XET_REQUIRE]']		= "\n\n\trequire DIR_UNITS . '<sample>/[route]/<sample>.structure.inc';";
					$prepareController['[CONTROLLER_USE]']				= 'Proj\[Route]\Structure';
					$prepareController['[CONTROLLER_EXTENDS]']			= 'Structure\<Sample>';
					$prepareController['[CONTROLLER_PARAM_ID]']			= '';
					$prepareController['[CONTROLLER_PARAM_NAME]']		= '';

					$prepareStructure = [
						'[STRUCTURE_REQUIRE]'		=> "require DIR_UNITS . '<sample>/<sample>.consts.inc';",
						'[STRUCTURE_USE_UNITS]'		=> "\n\tuse Base\Units;",
						'[STRUCTURE_USE_CONSTS]'	=> "\n\tuse Proj\Units\Consts;",
						'[STRUCTURE_USE_ACTIONS]'	=> '',
						'[STRUCTURE_EXTENDS]'		=> 'Units implements Consts\<Sample>',
						'[STRUCTURE_PARAM_ID]'		=> 'self::ID, ',
						'[STRUCTURE_PARAM_NAME]'	=> 'self::NAME, '
					];

					if ($binds & Consts\Composition::FILE_ACTIONS) {
						$prepareStructure['[STRUCTURE_REQUIRE]']		= "require DIR_UNITS . '<sample>/[route]/<sample>.actions.inc';";
						$prepareStructure['[STRUCTURE_USE_UNITS]']		= '';
						$prepareStructure['[STRUCTURE_USE_CONSTS]']		= '';
						$prepareStructure['[STRUCTURE_USE_ACTIONS]']	= "\n\tuse Proj\[Route]\Actions;";
						$prepareStructure['[STRUCTURE_EXTENDS]']		= 'Actions\<Sample>';
						$prepareStructure['[STRUCTURE_PARAM_ID]']		= '';
						$prepareStructure['[STRUCTURE_PARAM_NAME]']		= '';
					}

					$sampleStructure = file_get_contents(__DIR__ . '/samples/structure.sample');
					$sampleStructure = str_replace(array_keys($prepareStructure), $prepareStructure, $sampleStructure);
					$sampleStructure = str_replace(array_keys($replace), $replace, $sampleStructure);
					$this->WriteFile($routeDir, "{$unitName}.structure.inc", $sampleStructure);
				}
				if ($binds & Consts\Composition::FILE_MODEL) {
					$prepareController['[MODEL_REQUIRE]']				= "\n\trequire DIR_UNITS . '<sample>/[route]/<sample>.model.inc';";
					$prepareController['[MODEL_USE]']					= "\n\tuse Proj\[Route]\Model;";
					$prepareController['[MODEL_PROPERTY]']				= "\n\n\t\t" . 'private Model\<Sample> $model;';
					$prepareController['[MODEL_INSTANCE]']				= "\n\n\t\t\t" . '$this->model = Model\<Sample>::instance();';

					$sampleModel = file_get_contents(__DIR__ . '/samples/model.sample');
					$sampleModel = str_replace(array_keys($replace), $replace, $sampleModel);
					$this->WriteFile($routeDir, "{$unitName}.model.inc", $sampleModel);
				}

				$sampleController = file_get_contents(__DIR__ . '/samples/controller.sample');
				$sampleController = str_replace(array_keys($prepareController), $prepareController, $sampleController);

				foreach ($entries as $entry) {
					$entryName = strtolower($entry);

					$replace['[ENTRY]'] = strtoupper($entry);

					$sampleController = str_replace(array_keys($replace), $replace, $sampleController);
					$this->WriteFile($routeDir, "{$unitName}.controller.{$entryName}.inc", $sampleController);

					$file = fopen(DIR_UNITS . "{$replace['[route]']}.units.{$entryName}.inc", 'a');
					fwrite($file, "\n\trequire DIR_UNITS . '{$unitName}/{$replace['[route]']}/{$unitName}.controller.{$entryName}.inc';");
					fclose($file);
				}
			}
			$file = fopen(DIR_UNITS . 'consts.inc', 'a');
			fwrite($file, "\n\tconst ID_{$replace['<SAMPLE>']} = {$data['id']};");
			fclose($file);
		}

		public function CreateModel(string $name, string $unitName, string $routeName): void {
			$replace = [
				'[Route]' => ucfirst(strtolower($routeName)),
				'<Sample>' => ucfirst(strtolower($name))
			];
			$sampleModel = file_get_contents(__DIR__ . '/samples/model.sample');
			$sampleModel = str_replace(array_keys($replace), $replace, $sampleModel);
			$this->WriteFile(DIR_UNITS . "{$unitName}/{$routeName}/", "{$name}.model.inc", $sampleModel);
		}

		public function CreateEditor(string $name, string $unitName): void {
			$replace = [
				'<sample>' => strtolower($name),
				'<Sample>' => ucfirst(strtolower($name)),
				'[unit]' => strtolower($unitName)
			];
			foreach (Consts\Composition::ENTRIES as $entry) {
				$replace['[ENTRY]'] = strtoupper($entry);
				$sampleEditor = file_get_contents(__DIR__ . '/samples/editor.sample');
				$sampleEditor = str_replace(array_keys($replace), $replace, $sampleEditor);
				$this->WriteFile(DIR_UNITS . "{$unitName}/admin/editors/{$replace['<sample>']}/", "{$replace['<sample>']}.editor.{$entry}.inc", $sampleEditor);
			}

			$sampleEditorCommon = file_get_contents(__DIR__ . '/samples/editor.common.sample');
			$sampleEditorCommon = str_replace(array_keys($replace), $replace, $sampleEditorCommon);
			$this->WriteFile(DIR_UNITS . "{$unitName}/admin/editors/{$replace['<sample>']}/", "{$replace['<sample>']}.editor.common.inc", $sampleEditorCommon);

			$sampleEditorModel = file_get_contents(__DIR__ . '/samples/editor.model.sample');
			$sampleEditorModel = str_replace(array_keys($replace), $replace, $sampleEditorModel);
			$this->WriteFile(DIR_UNITS . "{$unitName}/admin/editors/{$replace['<sample>']}/", "{$replace['<sample>']}.editor.model.inc", $sampleEditorModel);
		}

		private function WriteFile(string $path, string $name, string $content) {
			if (!is_dir($path)) mkdir($path, 0777, true);
			file_put_contents($path . $name, $content);
		}

	}

	Composition::init();