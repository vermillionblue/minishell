#include "../includes/minishell.h"

char **list_to_arr(t_env **env_list)
{
	char	**new_arr;
	t_env	*temp;
	char	*holder;
	char	*full_path;
	int		i;
	
	i = 0;
	new_arr = malloc(env_list_size(env_list) + 1);
	new_arr[env_list_size(env_list) + 1] = 0;
	temp = *env_list;
	while(temp)
	{
		holder = ft_strjoin(temp->bash_variable, "=");
		full_path = ft_strjoin(holder, temp->bash_v_content);
		free(holder);
		new_arr[i] = ft_strdup(full_path);
		i++;
		temp = temp->next;
	}
	return (new_arr);
}

t_env	*create_env_list(char **envp)
{
	t_env	*env_list;
	char	**array;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	env_list = NULL;
	while (envp[i])
	{
		if (envp[i][ft_strlen(envp[i]) - 1] == '=')
		{
			array[0] = ft_strdup(envp[i]);
			array[1] = "";
		}
		else
			array = ft_split(envp[i], '=');
		append_env_element(&env_list, create_env_element(array));
		i++;
	}
	return (env_list);
}

void	append_env_element(t_env **env_list, t_env *new)
{
	t_env	*temp;

	temp = *env_list;
	if (*env_list)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		*env_list = new;
}
